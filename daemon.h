#ifndef DAEMON_H
#define DAEMON_H

void daemonize(void);
void main_loop(void);
void setup(void);
void handle_signal(int sig);
#endif
