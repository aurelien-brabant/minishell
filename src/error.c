#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/error.h"
#include "minishell/stat.h"

static const char	*g_error_messages[ERROR_MAX] = {
	"Dynamic memory allocation failed",
	"Found trailing pipe",
};

/*
** Print an error message on stderr and exit with exit code error + 1.
*/

int	error_print(t_error error)
{
	if (error == ERROR_ERRNO)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		return (errno);
	}
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", g_error_messages[error]);
	return (error + 1);
}

void	error_fatal(t_error error)
{
	minishell_exit(error_print(error));
}

void	*assert_ptr(void *p)
{
	if (p == NULL)
		error_fatal(ERROR_BADALLOC);
	return (p);
}

/*
** Handy shortcut to add elements to the temporary gc (stat->tmp_gc).
*/

void	*gc_add_tmp(void *el, void (*fn)(void *))
{
	t_gc	gc;

	gc = stat_get()->tmp_gc;
	assert_ptr(el);
	ft_gc_add(gc, el, fn);
	return (el);
}

void	*gc_add_global(void *el, void (*fn)(void *))
{
	t_gc	gc;

	gc = stat_get()->global_gc;
	assert_ptr(el);
	ft_gc_add(gc, el, fn);
	return (el);
}
