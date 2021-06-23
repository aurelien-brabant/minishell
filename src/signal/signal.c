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
	pid_t	*pid_loc;
	int		signaled;

	signaled = 0;
	if (g_pids != NULL)
	{
		pid_loc = g_pids;
		while (*pid_loc != -1)
		{
			if (*pid_loc != 0)
				kill(*pid_loc, sig);
			++pid_loc;
		}
		signaled = 1;
	}
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	if (!signaled)
	{
		rl_on_new_line();
		if (sig == SIGINT)
			rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
}
