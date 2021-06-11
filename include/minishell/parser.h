#ifndef PARSER_H
# define PARSER_H
# include "libft/vector.h"

typedef enum e_redirection_type
{
	REDIRECTION_NONE = -1,
	REDIRECTION_IN,
	REDIRECTION_DOUBLE_IN,
	REDIRECTION_OUT_APPEND,
	REDIRECTION_OUT_OVERRIDE,
	REDIRECTION_MAX,
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

t_pipeline	parser_invoke(char *input);

#endif
