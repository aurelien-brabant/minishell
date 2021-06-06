#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "libft/vector.h"
#include "libft/cstring.h"

#include "minishell/parser.h"
#include "minishell/minishell.h"
#include "minishell/lexer.h"

/*
t_simple_command	*simple_command_new(char **input, char *tok)
{
	t_simple_command	*sc;
	t_token_type		toktype;

	sc = malloc(sizeof (*sc));
	sc->name = tok; 
	while (1)
	{
		tok = get_token(input);
		if (tok == NULL)
			break ;
		toktype = get_token_type(get_chr_class(*tok));
		if (toktype == SPACE; |)
		tok = ft_strjoin(sc->name, tok);
		free(sc->name);
		sc->name = tok;
	}
	printf("Command name: %s\n", sc->name);
	return (sc);
}
*/

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
