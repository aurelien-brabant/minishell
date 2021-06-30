#include <unistd.h>

#include "libft/cstring.h"

#include "minishell/builtin.h"
#include "minishell/env.h"

int	builtin_env(int argc, char *argv[], bool forked)
{
	(void)argc;
	(void)argv;
	(void)forked;
	minishell_printenv();
	return (0);
}
