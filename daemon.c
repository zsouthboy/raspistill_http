#include "daemon.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
#define NAME "rpishd Daemon for Raspistill_http"
#define VERSION "0.1"

int main(int argc, char *argv[]) {
	if (argc > 1) {
		printf("%s version %s, compiled %s %s\n", NAME, VERSION, __DATE__, __TIME__);
		printf("https://github.com/zsouthboy/raspistill_http\n");
		exit(EXIT_SUCCESS);
	}
	setup();
	daemonize();
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
	if (signal(SIGINT, handle_signal) == SIG_ERR) {
		printf("Couldn't register signal handlers, bailing!");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGUSR1, handle_signal) == SIG_ERR) {
		printf("Couldn't register signal handlers, bailing!");
		exit(EXIT_FAILURE);
	}
}

void handle_signal(int sig) {
	if (sig == SIGINT || sig == SIGUSR1) {
		syslog(LOG_INFO, "Caught SIGINT/SIGUSR1, shutting down.");
		exit(EXIT_SUCCESS);
	}
}

