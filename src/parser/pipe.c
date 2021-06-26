#include <unistd.h>

#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/error.h"
#include "minishell/parser.h"

int	parse_pipe(t_vector pipeline, t_lexer *lexer, char *token)
{
	if (ft_strlen(token) > 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: unknown operator\n", token);
		return (1);
	}
	if (token_get_next(lexer, &token) == TOKEN_ERROR)
	{
		ft_dprintf(STDERR_FILENO, "minishell: trailing pipe\n", token);
		return (2);
	}
	ft_vector_append(pipeline,
			assert_ptr(command_new(ft_vector_length(pipeline))));
	return (0);
}
