#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

#include "libft/io.h"
#include "libft/cstring.h"

#include "minishell/minishell.h"
#include "minishell/constants.h"
#include "minishell/stat.h"
#include "minishell/parser.h"
#include "minishell/signal.h"
#include "minishell/env.h"

/*
** Invoke a minishell instance.
*/

int	minishell_invoke(unsigned int opt, char **optargs, char **envp)
{
	char		*cmd;
	t_vector	parsed;

	init_signal();
	stat_init(opt, optargs, envp);
	if (opt & (1 << OPTION_TYPE_COMMAND))
	{
		parser_invoke(optargs[OPTION_TYPE_COMMAND]);
		return (0);
	}
	init_signal();
	cmd = prompt_present();
	while (cmd != NULL)
	{
		parsed = parser_invoke(cmd);
		if (parsed != NULL)
			exec(parsed);
		else
			stat_get()->last_status_code = PARSING_ERROR;
		ft_gc_wipe(stat_get()->tmp_gc);
		cmd = prompt_present();
	}
	write(STDOUT_FILENO, "exit\n", 5);
	minishell_exit(EXIT_SUCCESS);
	return (0);
}

void	minishell_exit(int exit_status)
{
	stat_destroy();
	unlink(HERE_DOC_FILEPATH);
	exit(exit_status);
}
