#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

#include "minishell/signal.h"
#include "minishell/stat.h"
#include "minishell/constants.h"
#include "minishell/minishell.h"

static void	handle_sigint(int sig)
{
	bool	is_pid;

	(void)sig;
	is_pid = g_pid[PID_CHILD] != 0;
	if (is_pid)
		kill(g_pid[PID_CHILD], sig);
	stat_get()->last_status_code = 128 + sig;
	if (sig == SIGINT)
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
}
