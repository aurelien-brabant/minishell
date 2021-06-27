#ifndef PARSER_H
# define PARSER_H
# include "libft/vector.h"
# include "minishell/lexer.h"
# include "minishell/argv.h"

typedef enum e_redirection_type
{
	REDIRECTION_NONE = -1,
	REDIRECTION_OUT,
	REDIRECTION_IN,
	REDIRECTION_DIN,
	REDIRECTION_DOUT,
	REDIRECTION_MAX,
}	t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type	type;
	char				*arg;
}	t_redirection;

typedef struct s_command
{
	t_argv			*argv;
	t_vector		redir;
	size_t			id;
}	t_command;

t_vector	*parser_invoke(char *input);

int			parse_output_redirection(t_vector pipeline, t_lexer *lexer,
				char *token);
int			parse_input_redirection(t_vector pipeline, t_lexer *lexer,
				char *token);
t_command	*command_new(size_t id);
void		command_destroy(t_command *cmd);
int			parse_pipe(t_vector pipeline, t_lexer *lexer, char *token);
int			parse_word(t_vector pipeline, char *token);
char		*word_strip_quotes(char *word);
void		expand(t_vector pipeline, char *word);

#endif
