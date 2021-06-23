#include <unistd.h>

#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/io.h"

/* TODO: handle argument: exit [n] */

int	builtin_exit(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	write(STDOUT_FILENO, "exit\n", 5);
	minishell_exit(0);
	return (0);
}
