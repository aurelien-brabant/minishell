#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "libft/vector.h"
#include "libft/cstring.h"

#include "minishell/parser.h"
#include "minishell/minishell.h"
#include "minishell/lexer.h"
#include "minishell/stat.h"
#include "minishell/error.h"

static int print_token(char *string)
{
	puts(string);
	return (0);
}

t_vector	parser_invoke(char *input)
{
	t_lexer				*lexer;

	lexer = lexer_build(input);
	ft_vector_foreach(lexer->tokenv, &print_token, NULL);
	return (NULL);
}
