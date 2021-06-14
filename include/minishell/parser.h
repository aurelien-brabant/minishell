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
}	t_redirecton_type;

typedef struct s_redirection
{
	t_redirecton_type	type;
	char				*arg;
}	t_redirection;

typedef struct s_command
{
	char			*id;
	t_argv			*argv;
	t_redirection	*redir_in;
	t_vector		redir_out;
}	t_command;

t_vector	*parser_invoke(char *input);

void		parse_output_redirection(t_vector pipeline, t_lexer *lexer,
				char *token);
void		parse_input_redirection(t_vector pipeline, t_lexer *lexer, char *token);
t_command	*command_new(void);
void		parse_pipe(t_vector pipeline, t_lexer *lexer, char *token);
void		parse_word(t_vector pipeline, t_lexer *lexer, char *token);

#endif
