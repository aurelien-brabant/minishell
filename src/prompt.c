#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "libft/io.h"
#include "libft/ctype.h"

#include "minishell/minishell.h"
#include "minishell/constants.h"
#include "minishell/signal.h"

/*
** Present a shell prompt to the user, ready to accept a new command from
** STDIN.
** The readline GNU library is used to display a bash-like prompt with
** built-in support for history, path auto-completion, and so on.
*/

char	*prompt_present(void)
{
	char	*line;
	char	*prompt;

	prompt = "\033[0;34mminishell \033[0;36m» \033[0m";
	signal(SIGINT, handle_prompt_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = ft_gc_add(g_msh.gc_tmp, readline(prompt), &free);
	if (line != NULL && *line != '\0')
		add_history(line);
	return (line);
}
