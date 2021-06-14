#include "libft/vector.h"

#include "minishell/parser.h"

void	parse_word(t_vector pipeline, t_lexer *lexer, char *token)
{
	t_command		*cmd;
	t_redirection	*last_out_redir;

	last_out_redir = NULL;
	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	if (ft_vector_length(cmd->redir_out) > 0)
		last_out_redir = ft_vector_get(cmd->redir_out, ft_vector_length(cmd->redir_out) - 1);
	if (cmd->redir_in && cmd->redir_in->arg == NULL)
		cmd->redir_in->arg = token;
	else if (last_out_redir && last_out_redir->arg == NULL)
		last_out_redir->arg = token;
	else if (cmd->id == NULL)
		cmd->id = token;
	else
		argv_append(cmd->argv, token);
	token_consume(lexer);
}
