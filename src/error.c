#include <unistd.h>
#include <sys/errno.h>
#include <string.h>
#include <stdio.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/error.h"

void	*assert_ptr(void *p)
{
	if (p == NULL)
	{
		ft_dprintf(2, "minishell (fatal): %s\n", strerror(errno));
		minishell_exit(1);
	}
	return (p);
}

/*
** Handy shortcuts to quickly add pointers to garbage collectors
*/

void	*gc_add_tmp(void *el, void (*fn)(void *))
{
	t_gc	gc;

	gc = g_msh.gc_tmp;
	assert_ptr(el);
	ft_gc_add(gc, el, fn);
	return (el);
}

void	*gc_add_global(void *el, void (*fn)(void *))
{
	t_gc	gc;

	gc = g_msh.gc_glob;
	assert_ptr(el);
	ft_gc_add(gc, el, fn);
	return (el);
}
