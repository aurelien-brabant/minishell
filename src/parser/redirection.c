#include <unistd.h>
#include <stdio.h>

#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/parser.h"
#include "minishell/error.h"

/*
** TODO: REFACTOR THIS FILE, OUT AND IN REDIRECTIONS CAN BE HANDLED BY
** THE SAME FUNCTION TO AVOID DUPLICATING CODE
*/

static t_redir_type	redirection_get_type(char *token)
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

int	parse_output_redirection(t_pipeline *pipeline, t_lexer *lexer, char *token)
{
	t_command	*cmd;

	cmd = &pipeline->data[pipeline->len - 1];
	if (ft_strcmp(token, ">") != 0 && ft_strcmp(token, ">>") != 0)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: %s: invalid output redirection\n", token);
		return (1);
	}
	redirv_add(cmd->rv, redirection_get_type(token));
	if (token_get_next(lexer, &token) != TOKEN_WORD)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: valid arg required\n", token);
		return (2);
	}
	return (0);
}

int	parse_input_redirection(t_pipeline *pipeline, t_lexer *lexer, char *token)
{
	t_command		*cmd;

	cmd = &pipeline->data[pipeline->len - 1];
	if (ft_strcmp(token, "<") != 0 && ft_strcmp(token, "<<") != 0)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: %s: invalid input redirection\n", token);
		return (1);
	}
	redirv_add(cmd->rv, redirection_get_type(token));
	if (token_get_next(lexer, &token) != TOKEN_WORD)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: valid arg required\n", token);
		return (2);
	}
	return (0);
}
