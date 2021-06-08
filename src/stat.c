#include <stdlib.h>

#include "minishell/stat.h"

t_stat	*stat_get(void)
{
	static t_stat	stat = {
		.opt = 0, .optargs = NULL, .global_gc = NULL, .tmp_gc = NULL,
	};

	return (&stat);
}

void	stat_init(unsigned int opt, char **optargs)
{
	stat_get()->opt = opt;
	stat_get()->optargs = optargs;
	stat_get()->global_gc = ft_gc_new();
	stat_get()->tmp_gc = ft_gc_new();
	stat_get()->error = false;
}

void	stat_destroy(void)
{
	ft_gc_destroy(stat_get()->tmp_gc);
	ft_gc_destroy(stat_get()->global_gc);
}
