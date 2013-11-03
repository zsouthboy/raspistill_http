all:
	gcc -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/ daemon.c -o bin/rpishd

