#include <unistd.h>

#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/lexer.h"
#include "minishell/parser.h"

void	parse_pipe(t_vector pipeline, t_lexer *lexer, char *token)
{
	if (ft_strlen(token) > 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: unknown operator\n", token);
		return ;
	}
	if (token_get_next(lexer, &token) == TOKEN_ERROR)
	{
		ft_dprintf(STDERR_FILENO, "minishell: trailing pipe\n", token);
		return ;
	}
	ft_vector_append(pipeline, command_new());
}