#ifndef PARSER_H
# define PARSER_H
# include "libft/vector.h"
# include "minishell/lexer.h"

typedef struct s_ast_node
{
	t_token_type		type;
	void				*info;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
}	t_ast_node;	

typedef enum e_redirection_type
{
	REDIRECTION_NONE = -1,
	REDIRECTION_ONE,
	REDIRECTION_TWO,
}	t_redirection_type;

typedef	struct s_redirection
{
	char				*filepath;
	t_redirection_type	type;	
}	t_redirection;

typedef struct s_simple_command
{
	char			*id;
	t_vector		argv;
	t_redirection	redirection;	
}	t_simple_command;


/* A pipeline is a vector of t_simple_command */

typedef t_vector	t_pipeline;

typedef struct	s_parser
{
	t_vector	instructions;
}	t_parser;

t_ast_node	*parser_invoke(char *input);

t_ast_node	*ast_node_new(t_token_type type, void *info);
void		ast_node_insert(t_ast_node **root, t_ast_node *node);
void		ast_print(t_ast_node *root);

#endif
