#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

#include "libft/cstring.h"

#include "minishell/signal.h"
#include "minishell/constants.h"
#include "minishell/minishell.h"

static const char	*g_sig_msg[] = {
	[SIGINT] = "",
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

void	sig_send_to_all_children(int sig)
{
	pid_t	*pid_loc;

	pid_loc = g_msh.pids;
	while (*pid_loc != -1)
	{
		if (*pid_loc != 0)
			kill(*pid_loc, sig);
		++pid_loc;
	}
}

void	handle_prompt_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_msh.status = 128 + sig;
}
