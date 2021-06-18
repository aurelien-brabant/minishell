#include <stdlib.h>

#include "minishell/lexer.h"

#include "libft/vector.h"

void	lexer_destroy(t_lexer *lexer)
{
	ft_vector_destroy(lexer->tokenv, NULL);
	free(lexer);
}

t_lexer	*lexer_new(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof (*lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->tokenv = ft_vector_new(10);
	if (lexer->tokenv == NULL)
	{
		free(lexer);
		return (NULL);
	}
	lexer->current_token_index = 0;
	return (lexer);
}
