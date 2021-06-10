#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell/lexer.h"
#include "minishell/stat.h"
#include "minishell/error.h"

#include "libft/cstring.h"

char	*token_get(t_lexer *lexer)
{
	if (lexer->current_token_index >= ft_vector_length(lexer->tokenv))
		return (NULL);
	return (ft_vector_get(lexer->tokenv, lexer->current_token_index));	
}

char	*token_get_next(t_lexer *lexer)
{
	if (lexer->current_token_index + 1 >= ft_vector_length(lexer->tokenv))
		return (NULL);
	return (ft_vector_get(lexer->tokenv, lexer->current_token_index + 1));
}

void	token_consume(t_lexer *lexer)
{
	lexer->current_token_index++;
}
