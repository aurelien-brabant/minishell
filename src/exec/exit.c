#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "libft/io.h"
#include <stdio.h>
#include <stdlib.h>

int	fn_exit(char *argv[], size_t argc)
{
	(void)argc;
	(void)argv;
	ft_gc_wipe(stat_get()->tmp_gc);
	printf("exit\n");
	minishell_exit(0);
	return (0);
}
