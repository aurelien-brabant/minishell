#include <stdlib.h>

#include "libft/io.h"

#include "minishell/minishell.h"

static void	parse_tokens(char *cmd)
{
	char	*tok;
	
	ft_printf("token breakdown:\n");
	tok = get_token(&cmd);
	while (tok != NULL)
	{
		ft_printf("%s\n", tok);
		tok = get_token(&cmd);
	}
}

/*
** Invoke a minishell instance.
*/

int		minishell_invoke(unsigned int opt, char **optstr)
{
	char	*cmd;

	if (opt & (1 << OPTION_TYPE_COMMAND))
	{
		parse_tokens(optstr[OPTION_TYPE_COMMAND]);
		return (0);
	}
	while (1)
	{
		cmd = prompt_present("\033[0;34mminishell\033[0m-1.0$ ");
		parse_tokens(cmd);
		free(cmd);
	}
	return (0);
}
