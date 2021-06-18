#include "minishell/signal.h"
#include "minishell/minishell.h"
#include <stdio.h>
#include <signal.h>

static void	kill_pid(int sig)
{
	(void)sig;
	if (sig_pid)
		kill(sig_pid, SIGINT);
	printf("\n");
}

void	init_signal(void)
{
	signal(SIGINT, kill_pid);
}
