#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft/vector.h"
#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/parser.h"
#include "minishell/minishell.h"
#include "minishell/lexer.h"
#include "minishell/stat.h"
#include "minishell/error.h"

static int	parse(t_lexer *lexer, t_vector pipeline)
{
	char				*token;
	t_token_type		type;
	int					ret;

	type = token_get(lexer, &token);
	ret = 0;
	while (ret == 0 && type != TOKEN_ERROR)
	{
		if (ft_vector_length(pipeline) == 0)
			ft_vector_append(pipeline,
				assert_ptr(command_new(ft_vector_length(pipeline))));
		if (type == TOKEN_WORD)
			expand(pipeline, token);
		else if (type == TOKEN_OR)
			ret = parse_pipe(pipeline, lexer, token);
		else if (type == TOKEN_REDIRECTION_OUT)
			ret = parse_output_redirection(pipeline, lexer, token);
		else if (type == TOKEN_REDIRECTION_IN)
			ret = parse_input_redirection(pipeline, lexer, token);
		token_consume(lexer);
		type = token_get(lexer, &token);
	}
	return (ret);
}

/*
static int	print_command(t_command *cmd, int index)
{
	printf("COMMAND %d\n", index);
	for (size_t i = 0; i < cmd->argv->length; ++i) {
		printf("ARG %s\n", cmd->argv->args[i]);
	}
	for (size_t i = 0; i < ft_vector_length(cmd->redir_out); ++i) {
		t_redirection *redir = ft_vector_get(cmd->redir_out, i);
		printf("Redirection OUT:\nType: %d\nARG=%s\n", redir->type, redir->arg);
	}
	for (size_t i = 0; i < ft_vector_length(cmd->redir_in); ++i) {
		t_redirection *redir = ft_vector_get(cmd->redir_in, i);
		printf("Redirection IN:\nType: %d\nARG=%s\n", redir->type, redir->arg);
	}
	return (0);
}
*/

static void	destroy_pipeline(t_vector pipeline)
{
	ft_vector_destroy(pipeline, (void *)(void *)&command_destroy);
}

t_vector	*parser_invoke(char *input)
{
	t_lexer				*lexer;
	t_vector			pipeline;

	lexer = lexer_build(input);
	pipeline = ft_gc_add(stat_get()->tmp_gc,
			assert_ptr(ft_vector_new(5)), &destroy_pipeline);
	if (parse(lexer, pipeline) != 0)
		return (NULL);
	return (pipeline);
}
