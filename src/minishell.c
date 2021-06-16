#include <stdlib.h>
#include <stdio.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "minishell/parser.h"

/*
** Invoke a minishell instance.
*/

int	minishell_invoke(unsigned int opt, char **optargs, char **envp)
{
	char		*cmd;
	t_vector	parsed;

	stat_init(opt, optargs, envp);
	if (opt & (1 << OPTION_TYPE_COMMAND))
	{
		parser_invoke(optargs[OPTION_TYPE_COMMAND]);
		return (0);
	}
	while (1)
	{
		cmd = prompt_present("\033[0;33mminishell\033[0m-1.0$ ");
		if (cmd == NULL)
			continue ;
		parsed = parser_invoke(cmd);
		exec(parsed);
		ft_gc_wipe(stat_get()->tmp_gc);
	}
	minishell_exit(EXIT_SUCCESS);
	return (0);
}

void	minishell_exit(int exit_status)
{
	stat_destroy();
	exit(exit_status);
}
