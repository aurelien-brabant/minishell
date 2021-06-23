#ifndef SIGNAL_H
# define SIGNAL_H
# include <sys/unistd.h>
# define PID_CHILD 0
# define PID_PARENT 1

extern	pid_t	*g_pids;

void	init_signal(void);

#endif
