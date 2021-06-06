#ifndef PARSER_H
# define PARSER_H
# include "libft/vector.h"

typedef struct s_simple_command
{
	char		*name;
	t_vector	tokens;
}	t_simple_command;


/* A pipeline is a vector of t_simple_command */

typedef t_vector	t_pipeline;

typedef struct	s_parser
{
	t_vector	instructions;
}	t_parser;

t_pipeline	parser_invoke(char *input);

#endif
