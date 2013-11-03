rpishd:
	gcc -I/opt/vc/userland/ -I/opt/vc/include/interface/vmcs_host/linux/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/ daemon.c -o bin/rpishd

standalone_prototype:
	gcc -lraspicam -lmmal -lmmal_core -lmmal_util -I/opt/vc/userland/ standalone_camera_prototype.c -o bin/standalone

