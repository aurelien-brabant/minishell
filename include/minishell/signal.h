#ifndef SIGNAL_H
# define SIGNAL_H
# include <sys/unistd.h>

extern	pid_t	*g_pids;

void	init_signal(void);
void	print_sig_msg(int sig);

#endif
