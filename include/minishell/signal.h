#ifndef SIGNAL_H
# define SIGNAL_H
# include <sys/unistd.h>

extern pid_t	*g_pids;

void	print_sig_msg(int sig);
void	handle_prompt_sigint(int sig);
void	sig_send_to_all_children(int sig);

#endif
