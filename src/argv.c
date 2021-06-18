#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/core.h"

#include "minishell/argv.h"

static void	argv_resize(t_argv *argv)
{
	char	**tmp;

	tmp = argv->args;
	argv->args = ft_calloc(argv->cap * 2 + 1, sizeof (char *));
	ft_memcpy(argv->args, tmp, sizeof (char *) * argv->length);
	argv->cap *= 2;
}

t_argv	*argv_new(size_t size)
{
	t_argv	*argv;

	argv = ft_calloc(1, sizeof (*argv));
	if (argv == NULL)
		return (NULL);
	argv->args = ft_calloc(size + 1, sizeof (char *));
	if (argv->args == NULL)
		return (NULL);
	argv->cap = size;
	argv->length = 0;
	return (argv);
}

void	argv_append(t_argv *argv, char *arg)
{
	if (argv->length == argv->cap)
		argv_resize(argv);
	argv->args[argv->length++] = arg;
	argv->args[argv->length] = NULL;
}

void	argv_remove(t_argv *argv, size_t index)
{
	size_t	i;

	i = index;
	argv->length--;
	while (i < argv->length)
	{
		argv->args[i] = argv->args[i + 1];
		++i;
	}
	argv->args[i] = NULL;
}

void	argv_destroy(t_argv *argv, void (*fn)(char *arg))
{
	size_t	i;

	i = 0;
	if (fn != NULL)
	{
		while (argv->args[i] != NULL)
			fn(argv->args[i++]);
	}
	free(argv->args);
	free(argv);
}
