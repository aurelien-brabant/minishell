#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

#include "libft/cstring.h"

#include "minishell/signal.h"
#include "minishell/stat.h"
#include "minishell/constants.h"
#include "minishell/minishell.h"

static const char *g_sig_msg[] = {
	[SIGINT] = NULL,
	[SIGSEGV] = "Segmentation fault",
	[SIGQUIT] = "Quit",
	NULL,
};

void	print_sig_msg(int sig)
{
	if (g_sig_msg[sig] != NULL)
	{
		write(STDERR_FILENO, g_sig_msg[sig], ft_strlen(g_sig_msg[sig]));
		write(STDERR_FILENO, "\n", 1);
	}
}

/*
** Send the signal sig to all the currently running child processes…
** The global array of pid should be ended by -1.
** If a pid of 0 is encountered, it is not signaled.
*/

static void	signal_pids(int sig)
{
	pid_t	*pid_loc;

	if (g_pids != NULL)
	{
		pid_loc = g_pids;
		while (*pid_loc != -1)
		{
			if (*pid_loc != 0)
				kill(*pid_loc, sig);
			++pid_loc;
		}
	}
}

static void	handle_sigint(int sig)
{
	if (g_pids != NULL)
		signal_pids(sig);
	write(STDOUT_FILENO, "\n", 1);
	if (g_pids == NULL)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_sigquit(int sig)
{
	if (g_pids != NULL)
		signal_pids(sig);
	if (g_pids == NULL)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
