#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "libft/vector.h"
#include "libft/cstring.h"

#include "minishell/parser.h"
#include "minishell/minishell.h"
#include "minishell/lexer.h"

t_pipeline	parser_invoke(char *input)
{
	t_token				*tok;

	tok = get_token(&input);
	while (tok != NULL)
	{
		printf("%s\n", tok->value);
		tok = get_token(&input);
	}
	return (NULL);
}
