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

//TODO: calloc protection

static t_command	*command_new(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof (*cmd));
	cmd->argv = argv_new(5);
	cmd->redir_out = ft_vector_new(2);
	return (cmd);
}

static t_redirecton_type	redirection_get_type(char *token)
{
	static char	*strs[] = {
		[REDIRECTION_IN] = "<",
		[REDIRECTION_DIN] = "<<",
		[REDIRECTION_OUT] = ">",
		[REDIRECTION_DOUT] = ">>",
	};
	size_t		i;

	i = 0;
	while (i < REDIRECTION_MAX)
	{
		if (ft_strcmp(token, strs[i]) == 0)
			return (i);
		++i;
	}
	return (REDIRECTION_NONE);
}

static t_redirection	*redirection_new(void)
{
	t_redirection	*redirection;
	
	redirection = ft_calloc(1, sizeof (*redirection));
	return (redirection);
}

static void	parse_word(t_vector pipeline, t_lexer *lexer, char *token)
{
	t_command		*cmd;
	t_redirection	*last_out_redir;

	last_out_redir = NULL;
	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	if (ft_vector_length(cmd->redir_out) > 0)
		last_out_redir = ft_vector_get(cmd->redir_out, ft_vector_length(cmd->redir_out) - 1);
	if (cmd->redir_in && cmd->redir_in->arg == NULL)
		cmd->redir_in->arg = token;
	else if (last_out_redir && last_out_redir->arg == NULL)
		last_out_redir->arg = token;
	else if (cmd->id == NULL)
		cmd->id = token;
	else
		argv_append(cmd->argv, token);
	token_consume(lexer);
}

static void	parse_or(t_vector pipeline, t_lexer *lexer, char *token)
{
	if (ft_strlen(token) > 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: unknown operator\n", token);
		return ;
	}
	ft_vector_append(pipeline, command_new());
	token_consume(lexer);
}

static void	parse_input_redirection(t_vector pipeline, t_lexer *lexer, char *token)
{
	t_command	*cmd;

	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	if (ft_strcmp(token, "<") != 0 && ft_strcmp(token, "<<") != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: invalid input redirection\n", token);
		return ;
	}
	if (cmd->redir_in == NULL)
		cmd->redir_in = redirection_new();
	cmd->redir_in->type = redirection_get_type(token);
	token_consume(lexer);
}

static void	parse_output_redirection(t_vector pipeline, t_lexer *lexer, char *token)
{
	t_command		*cmd;
	t_redirection	*redir;

	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	if (ft_strcmp(token, ">") != 0 && ft_strcmp(token, ">>") != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: invalid output redirection\n", token);
		return ;
	}
	redir = redirection_new();
	redir->type = redirection_get_type(token);
	ft_vector_append(cmd->redir_out, redir);
	token_consume(lexer);
}

static void	parse(t_lexer *lexer, t_vector pipeline)
{
	char				*token;
	t_token_type		type;

	type = token_get(lexer, &token);
	while (type != TOKEN_ERROR)
	{
		if (ft_vector_length(pipeline) == 0)
			ft_vector_append(pipeline, command_new());
		if (type == TOKEN_WORD)
			parse_word(pipeline, lexer, token);
		else if (type == TOKEN_OR)
			parse_or(pipeline, lexer, token);
		else if (type == TOKEN_REDIRECTION_OUT)
			parse_output_redirection(pipeline, lexer, token);
		else if (type == TOKEN_REDIRECTION_IN)
			parse_input_redirection(pipeline, lexer, token);
		type = token_get(lexer, &token);
	}
}

static int	print_command(t_command *cmd, int index)
{
	printf("COMMAND %d\n", index);
	printf("ID: %s\n", cmd->id);
	for (size_t i = 0; i < cmd->argv->length; ++i) {
		printf("ARG %s\n", cmd->argv->args[i]);
	}
	if (cmd->redir_in != NULL)
		printf("Redirection IN:\nType: %d\nARG=%s\n", cmd->redir_in->type, cmd->redir_in->arg);
	for (size_t i = 0; i < ft_vector_length(cmd->redir_out); ++i) {
		t_redirection *redir = ft_vector_get(cmd->redir_out, i);
		printf("Redirection OUT:\nType: %d\nARG=%s\n", redir->type, redir->arg);
	}
	return (0);
}

t_vector	*parser_invoke(char *input)
{
	t_lexer				*lexer;
	t_vector			pipeline;

	lexer = lexer_build(input);
	pipeline = ft_vector_new(5);
	if (pipeline == NULL)
		return (NULL);
	parse(lexer, pipeline);
	ft_vector_foreach(pipeline, &print_command, NULL);
	return (pipeline);
}
