#include <stdio.h>
#include <errno.h>

#include "bcm_host.h"
#include "interface/vcos/vcos.h"
#include "interface/mmal/mmal.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"
#include "host_applications/linux/apps/raspicam/RaspiCamControl.h"

/* defines from raspistill.c directly */
#define CAMERA_NUMBER 0
#define MMAL_CAMERA_PREVIEW_PORT 0
#define MMAL_CAMERA_VIDEO_PORT 1
#define MMAL_CAMERA_CAPTURE_PORT 2
#define STILLS_FRAME_RATE_NUM 15
#define STILLS_FRAME_RATE_DEN 1
#define VIDEO_OUTPUT_BUFFERS_NUM 3

#define WIDTH 800;
#define HEIGHT 600;


int main(void);
static void camera_control_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer);

int main(void){
	/* set up the camera connection and buffers */
	/* used https://github.com/tasanakorn/rpi-mmal-demo/blob/master/main.c as guide */
	/* and https://github.com/raspberrypi/userland/blob/master/host_applications/linux/apps/raspicam/RaspiStill.c */
	MMAL_COMPONENT_T *camera = 0;
	MMAL_ES_FORMAT_T *format;
	MMAL_STATUS_T status;
	MMAL_PORT_T *preview_port = NULL, *video_port = NULL, *still_port = NULL;
	MMAL_CONNECTION_T *camera_capture_connection = 0;
	bcm_host_init();
	status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA, &camera);
	if (status != MMAL_SUCCESS) {
		printf("Couldn't initialize camera. Status was %i. Bailing!", status);
		goto error;
	}
	preview_port = camera->output[MMAL_CAMERA_PREVIEW_PORT];
	video_port = camera->output[MMAL_CAMERA_VIDEO_PORT];
	still_port = camera->output[MMAL_CAMERA_CAPTURE_PORT];
	status = mmal_port_enable(camera->control, camera_control_callback);

	if (status != MMAL_SUCCESS) {
		printf("Unable to enable control port : error %d", status);
		goto error;
	}
      MMAL_PARAMETER_CAMERA_CONFIG_T cam_config =
      {
         { MMAL_PARAMETER_CAMERA_CONFIG, sizeof(cam_config) },
         .max_stills_w = WIDTH,
         .max_stills_h = HEIGHT,
         .stills_yuv422 = 0,
         .one_shot_stills = 1,
         .max_preview_video_w = 1024,
         .max_preview_video_h = 768,
         .num_preview_video_frames = 3,
         .stills_capture_circular_buffer_height = 0,
         .fast_preview_resume = 0,
         .use_stc_timestamp = MMAL_PARAM_TIMESTAMP_MODE_RESET_STC
      };

	mmal_port_parameter_set(camera->control, &cam_config.hdr);
	RASPICAM_CAMERA_PARAMETERS camera_parameters;
	raspicamcontrol_set_all_parameters(camera, camera_parameters);

	format = still_port->format;
   format->encoding = MMAL_ENCODING_OPAQUE;
   format->es->video.width = WIDTH;
   format->es->video.height = HEIGHT;
   format->es->video.crop.x = 0;
   format->es->video.crop.y = 0;
   format->es->video.crop.width = WIDTH;
   format->es->video.crop.height = HEIGHT;
   format->es->video.frame_rate.num = STILLS_FRAME_RATE_NUM;

   if (status != MMAL_SUCCESS)
   {
      printf("camera still format couldn't be set");
      goto error;
   }

   /* Ensure there are enough buffers to avoid dropping frames */
   if (still_port->buffer_num < VIDEO_OUTPUT_BUFFERS_NUM)
      still_port->buffer_num = VIDEO_OUTPUT_BUFFERS_NUM;

   /* Enable component */
   status = mmal_component_enable(camera);

   if (status != MMAL_SUCCESS)
   {
      printf("camera component couldn't be enabled");
      goto error;
   }
	goto error;

	return status;
error:	
	if (camera) {
		mmal_component_destroy(camera);
	}
	return status;
}

/* it looks like i need this callback which does nothing per raspistill.c. copied verbatim */
static void camera_control_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   if (buffer->cmd == MMAL_EVENT_PARAMETER_CHANGED)
   {
   }
   else
   {
      printf("Received unexpected camera control callback event, 0x%08x", buffer->cmd);
   }

   mmal_buffer_header_release(buffer);
}
 
