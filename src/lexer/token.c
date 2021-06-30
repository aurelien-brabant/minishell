#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell/lexer.h"
#include "minishell/error.h"

#include "libft/cstring.h"

t_token_type	token_get(t_lexer *lexer, char **token)
{
	if (lexer->current_token_index >= lexer->tokenv->len)
		return (TOKEN_ERROR);
	*token = lexer->tokenv->data[lexer->current_token_index];
	return (token_get_type(*token));
}

t_token_type	token_get_next(t_lexer *lexer, char **token)
{
	if (lexer->current_token_index + 1 >= lexer->tokenv->len)
		return (TOKEN_ERROR);
	*token = lexer->tokenv->data[lexer->current_token_index + 1];
	return (token_get_type(*token));
}

void	token_consume(t_lexer *lexer)
{
	lexer->current_token_index++;
}
