#include "libft/io.h"
#include "libft/cstring.h"

#include "minishell/datastructure.h"
#include "minishell/lexer.h"

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

int	parse_redirection(t_pipeline *pipeline, t_lexer *lexer, char *token)
{
	t_command		*cmd;
	t_redir_type	rtype;
	char			*tmp;

	cmd = &pipeline->data[pipeline->len - 1];
	rtype = redirection_get_type(token);
	if (rtype == REDIRECTION_NONE)
	{
		ft_dprintf(2, "minishell: unknown operator \"%s\"\n", token);
		return (1);
	}
	tmp = token;
	if (token_get_next(lexer, &token) != TOKEN_WORD)
	{
		ft_dprintf(2, "Redirection operator \"%s\""
			" requires a valid argument\n", tmp);
		return (1);
	}
	redirv_add(cmd->rv, rtype);
	return (0);
}

int	parse_pipe(t_pipeline *pipeline, t_lexer *lexer, char *token)
{
	if (ft_strlen(token) > 1)
	{
		ft_dprintf(2, "minishell: %s: unknown operator\n", token);
		return (1);
	}
	if (token_get_next(lexer, &token) == TOKEN_ERROR)
	{
		ft_dprintf(2, "minishell: trailing pipe\n", token);
		return (2);
	}
	pipeline_add(pipeline, pipeline->len);
	return (0);
}
