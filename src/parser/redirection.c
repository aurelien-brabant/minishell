#include <unistd.h>

#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/parser.h"

static t_redirecton_type	redirection_get_type(char *token)
{
	static char	*strs[] = {
		[REDIRECTION_IN] = "<",
		[REDIRECTION_DIN] = "<<",
		[REDIRECTION_OUT] = ">",
		[REDIRECTION_DOUT] = ">>",
	};
	size_t		i;

	i = 0;
	while (i < REDIRECTION_MAX)
	{
		if (ft_strcmp(token, strs[i]) == 0)
			return (i);
		++i;
	}
	return (REDIRECTION_NONE);
}

static t_redirection	*redirection_new(void)
{
	t_redirection	*redirection;
	
	redirection = ft_calloc(1, sizeof (*redirection));
	return (redirection);
}

void	parse_output_redirection(t_vector pipeline, t_lexer *lexer, char *token)
{
	t_command		*cmd;
	t_redirection	*redir;

	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	if (ft_strcmp(token, ">") != 0 && ft_strcmp(token, ">>") != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: invalid output redirection\n", token);
		return ;
	}
	redir = redirection_new();
	redir->type = redirection_get_type(token);
	ft_vector_append(cmd->redir_out, redir);
	if (token_get_next(lexer, &token) != TOKEN_WORD)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: valid arg required\n", token);
		return ;
	}
}

void	parse_input_redirection(t_vector pipeline, t_lexer *lexer, char *token)
{
	t_command	*cmd;

	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	if (ft_strcmp(token, "<") != 0 && ft_strcmp(token, "<<") != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: invalid input redirection\n", token);
		return ;
	}
	if (cmd->redir_in == NULL)
		cmd->redir_in = redirection_new();
	cmd->redir_in->type = redirection_get_type(token);
	if (token_get_next(lexer, &token) != TOKEN_WORD)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: valid arg required\n", token);
		return ;
	}
}
