#include "daemon.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

int main(void) {
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
		openlog("raspistill_http_daemon", LOG_PID, LOG_DAEMON);
		syslog(LOG_INFO, "Starting daemon");

		/* next let's set a umask of 0 - just in case we create files later */
		umask(0);

		/* close all our ties to the outside world since we're a daemon */
        	close(STDIN_FILENO);
        	close(STDOUT_FILENO);
        	close(STDERR_FILENO);

		syslog(LOG_INFO, "We're done, going home.");
		exit(EXIT_SUCCESS);
	}
	else {
		/* parent can exit now */
		exit(EXIT_SUCCESS);
	}
}	

void main_loop() {
	while (1) {
		sleep(1);
	}
}
