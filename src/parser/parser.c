#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft/vector.h"
#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/parser.h"
#include "minishell/minishell.h"
#include "minishell/lexer.h"
#include "minishell/stat.h"
#include "minishell/error.h"

/*
static int print_token(char *string)
{
	puts(string);
	return (0);
}
*/

static t_redirection_type	get_redirection_type(char *token)
{
	static char	*redirections[REDIRECTION_MAX] = {
		[REDIRECTION_IN] = "<",
		[REDIRECTION_DOUBLE_IN] = "<<",
		[REDIRECTION_OUT_OVERRIDE] = ">",
		[REDIRECTION_OUT_APPEND] = ">>",
	};
	size_t		i;

	i = 0;
	while (i < REDIRECTION_MAX)
	{
		if (ft_strcmp(redirections[i], token) == 0)
			return (i);
		++i;
	}
	return (REDIRECTION_NONE);
}

static void	parse(t_lexer *lexer)
{
	char				*token;
	t_token_type		type;
	t_redirection_type	redirection_type;

	type = token_get(lexer, &token);
	if (type == TOKEN_ERROR)
		return ;
	if (type == TOKEN_WORD)
	{
		printf("Command ID: %s\n", token);
		token_consume(lexer);
		while ((token_get(lexer, &token)) == TOKEN_WORD)
		{
			printf("ARG: \"%s\"\n", token);
			token_consume(lexer);
		}
	}
	else if (type == TOKEN_OR)
	{
		if (ft_strlen(token) > 1)
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: unknown operator\n", token);
			return ;
		}
		printf("PIPE\n");
		token_consume(lexer);
	}
	else if (type == TOKEN_REDIRECTION)
	{
		redirection_type = get_redirection_type(token);
		if (redirection_type == REDIRECTION_NONE)
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: unknown operator\n", token);
			return ;
		}
		printf("REDIRECTION: %s\n", token);
		if (token_get_next(lexer, &token) != TOKEN_WORD)
		{
			ft_dprintf(STDERR_FILENO, "Redirection operator \"%s\" expects a valid argument\n", token);
			return ;
		}
		token_consume(lexer);
		printf("REDIRECTION ARG: %s\n", token);
		token_consume(lexer);
		token_consume(lexer);
	}
	parse(lexer);
}

t_vector	parser_invoke(char *input)
{
	t_lexer				*lexer;

	lexer = lexer_build(input);
	parse(lexer);
	//ft_vector_foreach(lexer->tokenv, &print_token, NULL);
	return (NULL);
}
