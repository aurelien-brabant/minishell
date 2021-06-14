/*
** A simple arg vector implementation to make things easier
*/

#ifndef ARGV_H
# include <stddef.h>
# define ARGV_H

typedef struct s_argv
{
	size_t	length;
	size_t	cap;
	char	**args;
}	t_argv;

t_argv	*argv_new(size_t size);
void	argv_append(t_argv *argv, char *arg);
void	argv_destroy(t_argv *argv, void (*fn)(char *arg));

#endif
