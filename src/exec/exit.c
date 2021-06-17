#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "libft/io.h"
#include <stdio.h>
#include <stdlib.h>

void	fn_exit(void)
{
	ft_gc_wipe(stat_get()->tmp_gc);
	printf("exit\n");
	exit(0);
}
