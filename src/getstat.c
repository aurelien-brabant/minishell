#include <stdlib.h>

#include "minishell/stat.h"

t_stat	*getstat(void)
{
	static t_stat	stat = {
		.opt = 0, .optargs = NULL, .global_gc = NULL, .tmp_gc = NULL,
	};

	return (&stat);
}
