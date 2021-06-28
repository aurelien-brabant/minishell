#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"
#include "libft/io.h"

int	builtin_pwd(int argc, char *argv[], bool forked)
{
	char	*pwd;
	char	buf[PATH_MAX];

	(void)forked;
	(void)argv;
	(void)argc;
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		return (1);
	ft_printf("%s\n", pwd);
	return (0);
}
