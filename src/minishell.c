#include <stdlib.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "minishell/parser.h"

/*
** Invoke a minishell instance.
*/

int		minishell_invoke(unsigned int opt, char **optargs)
{
	char	*cmd;

	getstat()->opt = opt;
	getstat()->optargs = optargs;
	if (opt & (1 << OPTION_TYPE_COMMAND))
	{
		parser_invoke(optargs[OPTION_TYPE_COMMAND]);
		return (0);
	}
	while (1)
	{
		cmd = prompt_present("minishell> ");
		parser_invoke(cmd);
	}
	return (0);
}
