#ifndef PARSER_H
# define PARSER_H
# include "libft/vector.h"
# include "minishell/lexer.h"
# include "minishell/argv.h"

typedef enum e_node_type
{
	NODE_WORD = 1,
	NODE_REDIR_OUT,
	NODE_REDIR_IN,
	NODE_PIPE,

}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	void				*info;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
}	t_ast_node;	

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

/*
** REDIRECTION
*/
void	parse_output_redirection(t_vector pipeline, t_lexer *lexer,
			char *token);
void	parse_input_redirection(t_vector pipeline, t_lexer *lexer, char *token);

/*
** COMMAND
*/

t_command	*command_new(void);

/*
** PIPE
*/

void		parse_pipe(t_vector pipeline, t_lexer *lexer, char *token);

/*
** WORD
*/

void		parse_word(t_vector pipeline, t_lexer *lexer, char *token);

t_ast_node	*ast_node_new(t_node_type type, void *info);
void		ast_node_insert(t_ast_node **root, t_ast_node *node);
void		ast_print(t_ast_node *root);

#endif
