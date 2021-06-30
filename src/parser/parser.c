#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/parser.h"
#include "minishell/minishell.h"
#include "minishell/lexer.h"
#include "minishell/error.h"

static int	parse(t_lexer *lexer, t_pipeline *pipeline)
{
	char				*token;
	t_token_type		type;
	int					ret;

	type = token_get(lexer, &token);
	ret = 0;
	while (ret == 0 && type != TOKEN_ERROR)
	{
		if (pipeline->len == 0)
			pipeline_add(pipeline, pipeline->len);
		if (type == TOKEN_WORD)
			expand(pipeline, token);
		else if (type == TOKEN_OR)
			ret = parse_pipe(pipeline, lexer, token);
		else if (type == TOKEN_REDIRECTION_OUT || type == TOKEN_REDIRECTION_IN)
			ret = parse_redirection(pipeline, lexer, token);
		token_consume(lexer);
		type = token_get(lexer, &token);
	}
	return (ret);
}

/*
static int	print_pipeline(t_pipeline *pipeline)
{
	for (size_t i = 0; i < pipeline->len; ++i) {
		printf("COMMAND %ld\n", pipeline->data[i].id);
		for (size_t j = 0; j < pipeline->data[i].sv->len; ++j) {
			printf("ARG: \"%s\"\n", pipeline->data[i].sv->data[j]);
		}
		for (size_t j = 0; j < pipeline->data[i].rv->len; ++j) {
			printf("REDIR_TYPE: \"%d\"\n", pipeline->data[i].rv->data[j].type);
		}
		printf("\n");
	}
	return (0);
}
*/

t_pipeline	*parser_invoke(char *input)
{
	t_lexer				*lexer;
	t_pipeline			*pipeline;

	lexer = lexer_build(input);
	pipeline = gc_add_tmp(pipeline_new(10), (void *)(void *)&pipeline_destroy); 
	if (parse(lexer, pipeline) != 0)
		return (NULL);
	return (pipeline);
}
