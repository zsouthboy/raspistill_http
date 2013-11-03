#include "daemon.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>

#include "bcm_host.h"
#include "interface/vcos/vcos.h"
#include "interface/mmal/mmal.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"

#define NAME "rpishd Daemon for Raspistill_http"
#define VERSION "0.1"

/* defines from raspistill.c directly */
#define CAMERA_NUMBER 0
#define MMAL_CAMERA_PREVIEW_PORT 0
#define MMAL_CAMERA_VIDEO_PORT 1
#define MMAL_CAMERA_CAPTURE_PORT 2
#define STILLS_FRAME_RATE_NUM 15
#define STILLS_FRAME_RATE_DEN 1

int main(int argc, char *argv[]) {
	if (argc > 1) {
		printf("%s version %s, compiled %s %s\n", NAME, VERSION, __DATE__, __TIME__);
		printf("https://github.com/zsouthboy/raspistill_http\n");
		exit(EXIT_SUCCESS);
	}
	daemonize();
	setup();
	main_loop();
	return 0;
}

void daemonize(void) {
	pid_t p, s;
	p = fork();
	if (p == (pid_t) -1) {
		exit(EXIT_FAILURE);	
	}
	else if (p == (pid_t) 0) {
		/* we're the child */
		/* first we need to get a new sid so we're not an orphan after parent exits*/
		s = setsid();
		if (s < (pid_t) 0) {
			exit(EXIT_FAILURE);
		}

		/* we'll be sending messages to syslog, set it up to include our PID and throw messages where the system likes for daemons */
		openlog("rpishd", LOG_PID, LOG_DAEMON);
		syslog(LOG_INFO, "Starting daemon");

		/* next let's set a umask of 0 - just in case we create files later */
		umask(0);

		/* close all our ties to the outside world since we're a daemon */
        	close(STDIN_FILENO);
        	close(STDOUT_FILENO);
        	close(STDERR_FILENO);
	}
	else {
		/* parent can exit now */
		exit(EXIT_SUCCESS);
	}
}	

void main_loop(void) {
	while (1) {
		sleep(1);
	}
}

void setup(void) {
	/* setup our process to receive signals to our handler */
	if (signal(SIGTERM, handle_signal) == SIG_ERR) {
		printf("Couldn't register signal handlers, bailing!");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGUSR1, handle_signal) == SIG_ERR) {
		printf("Couldn't register signal handlers, bailing!");
		exit(EXIT_FAILURE);
	}
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
		syslog(LOG_CRIT, "Couldn't initialize camera. Status was %i. Bailing!", status);
		exit(EXIT_FAILURE);
	}
	syslog(LOG_INFO, "Somehow was able to connect the camera. Impressed.");
	exit(EXIT_SUCCESS);
}

void handle_signal(int sig) {
	if (sig == SIGTERM || sig == SIGUSR1) {
		syslog(LOG_INFO, "Caught SIGTERM/SIGUSR1, shutting down.");
		/* closing the syslog for our program is optional, but why not */
		closelog();
		exit(EXIT_SUCCESS);
	}
}

