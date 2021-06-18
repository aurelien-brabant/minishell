#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

#include "minishell/signal.h"
#include "minishell/stat.h"
#include "minishell/constants.h"
#include "minishell/minishell.h"

static void	kill_pid(int sig)
{
	bool	is_pid;

	(void)sig;
	is_pid = sig_pid != 0;
	if (is_pid)
		kill(sig_pid, SIGINT);
	stat_get()->last_status_code = 128 + sig;
	write(STDOUT_FILENO, "\n", 1);
	if (!is_pid)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, kill_pid);
}
