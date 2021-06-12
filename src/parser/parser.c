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

static void	parse(t_lexer *lexer, t_ast_node **root)
{
	char				*token;
	t_token_type		type;

	type = token_get(lexer, &token);
	while (type != TOKEN_ERROR)
	{
		if (type == TOKEN_WORD)
		{
			ast_node_insert(root, ast_node_new(NODE_WORD, token));
			token_consume(lexer);
		}
		else if (type == TOKEN_OR)
		{
			if (ft_strlen(token) > 1)
			{
				ft_dprintf(STDERR_FILENO, "minishell: %s: unknown operator\n", token);
				return ;
			}
			ast_node_insert(root, ast_node_new(NODE_PIPE, NULL));
			token_consume(lexer);
		}
		else if (type == TOKEN_REDIRECTION_OUT)
		{
			if (ft_strcmp(token, ">") != 0 && ft_strcmp(token, ">>") != 0)
			{
				ft_dprintf(STDERR_FILENO, "minishell: %s: invalid output redirection\n", token);
				return ;
			}
			if (token_get_next(lexer, &token) != TOKEN_WORD)
			{
				ft_dprintf(STDERR_FILENO, "Output redirection \"%s\" expects a file as an argument\n", token);
				return ;
			}
			token_get(lexer, &token);
			ast_node_insert(root, ast_node_new(NODE_REDIR_OUT, token));
			token_consume(lexer);
		}
		else if (type == TOKEN_REDIRECTION_IN)
		{
			if (ft_strcmp(token, "<") != 0 && ft_strcmp(token, "<<") != 0)
			{
				ft_dprintf(STDERR_FILENO, "minishell: %s: invalid input redirection\n", token);
				return ;
			}
			if (token_get_next(lexer, &token) != TOKEN_WORD)
			{
				ft_dprintf(STDERR_FILENO, "Input redirection \"%s\" expects an argument\n", token);
				return ;
			}
			token_get(lexer, &token);
			ast_node_insert(root, ast_node_new(NODE_REDIR_IN, token));
			token_consume(lexer);
		}
		type = token_get(lexer, &token);
	}
}

t_ast_node	*parser_invoke(char *input)
{
	t_lexer				*lexer;
	t_ast_node			*root;

	root = NULL;
	lexer = lexer_build(input);
	parse(lexer, &root);
	ast_print(root);
	return (root);
}
