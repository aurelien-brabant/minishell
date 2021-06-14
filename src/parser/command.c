#include "libft/core.h"

#include "minishell/parser.h"

t_command	*command_new(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof (*cmd));
	cmd->argv = argv_new(5);
	cmd->redir_out = ft_vector_new(2);
	return (cmd);
}
