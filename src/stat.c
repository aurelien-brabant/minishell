#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "minishell/minishell.h"
#include "minishell/stat.h"

t_stat	*stat_get(void)
{
	static t_stat	stat = {
		.opt = 0, .optargs = NULL, .global_gc = NULL, .tmp_gc = NULL,
		.env = NULL,
	};

	return (&stat);
}

void	stat_init(unsigned int opt, char **optargs, char **envp)
{
	stat_get()->opt = opt;
	stat_get()->optargs = optargs;
	stat_get()->global_gc = ft_gc_new();
	stat_get()->tmp_gc = ft_gc_new();
	stat_get()->env = stringv_new(70);
	while (*envp != NULL)
		stringv_add(stat_get()->env, *envp++);
}

void	stat_destroy(void)
{
	unlink(HERE_DOC_FILEPATH);
	stringv_destroy(stat_get()->env);
	ft_gc_destroy(stat_get()->tmp_gc);
	ft_gc_destroy(stat_get()->global_gc);
}
