#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

#include "minishell/signal.h"
#include "minishell/constants.h"
#include "minishell/minishell.h"

static void	kill_pid(int sig)
{
	(void)sig;
	if (sig_pid)
		kill(sig_pid, SIGINT);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	signal(SIGINT, kill_pid);
}
