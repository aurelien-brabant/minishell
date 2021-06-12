#ifndef PARSER_H
# define PARSER_H
# include "libft/vector.h"
# include "minishell/lexer.h"

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


t_ast_node	*parser_invoke(char *input);

t_ast_node	*ast_node_new(t_node_type type, void *info);
void		ast_node_insert(t_ast_node **root, t_ast_node *node);
void		ast_print(t_ast_node *root);

#endif
