#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell/lexer.h"
#include "minishell/stat.h"
#include "minishell/error.h"

#include "libft/cstring.h"

t_token_type	token_get(t_lexer *lexer, char **token)
{
	if (lexer->current_token_index >= ft_vector_length(lexer->tokenv))
		return (TOKEN_ERROR);
	*token = ft_vector_get(lexer->tokenv, lexer->current_token_index);
	return (token_get_type(*token));
}

t_token_type	token_get_next(t_lexer *lexer, char **token)
{
	if (lexer->current_token_index + 1 >= ft_vector_length(lexer->tokenv))
		return (TOKEN_ERROR);
	*token = ft_vector_get(lexer->tokenv, lexer->current_token_index + 1);
	return (token_get_type(*token));
}

void	token_consume(t_lexer *lexer)
{
	lexer->current_token_index++;
}
