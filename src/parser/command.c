#include <stdlib.h>

#include "libft/core.h"

#include "minishell/parser.h"

t_command	*command_new(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof (*cmd));
	cmd->argv = argv_new(5);
	cmd->redir = ft_vector_new(2);
	return (cmd);
}

void	command_destroy(t_command *cmd)
{
	ft_vector_destroy(cmd->redir, &free);
	argv_destroy(cmd->argv, (void *)(char *)&free);
	free(cmd);
}
