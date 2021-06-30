#include <stdlib.h>

#include "minishell/lexer.h"
#include "minishell/datastructure.h"

void	lexer_destroy(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < lexer->tokenv->len)
		free(lexer->tokenv->data[i++]);
	stringv_destroy(lexer->tokenv);
	free(lexer);
}

t_lexer	*lexer_new(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof (*lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->tokenv = stringv_new(10);
	if (lexer->tokenv == NULL)
	{
		free(lexer);
		return (NULL);
	}
	lexer->current_token_index = 0;
	return (lexer);
}
