#include <stdlib.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "minishell/parser.h"

/*
** Invoke a minishell instance.
*/

int	minishell_invoke(unsigned int opt, char **optargs)
{
	char	*cmd;

	stat_init(opt, optargs);
	if (opt & (1 << OPTION_TYPE_COMMAND))
	{
		parser_invoke(optargs[OPTION_TYPE_COMMAND]);
		return (0);
	}
	while (1)
	{
		cmd = prompt_present("\033[0;33mminishell\033[0m-1.0$ ");
		parser_invoke(cmd);
		ft_gc_wipe(stat_get()->tmp_gc);
	}
	ft_gc_destroy(stat_get()->tmp_gc);
	stat_destroy();
	return (0);
}
