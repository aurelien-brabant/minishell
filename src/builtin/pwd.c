#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"
#include "libft/io.h"

char	*get_pwd(void)
{
	char	buf[PATH_MAX];

	return (getcwd(buf, PATH_MAX));
}

int	builtin_pwd(int argc, char *argv[])
{
	char	*pwd;

	(void)argv;
	(void)argc;
	pwd = ft_strdup(get_pwd());
	if (!pwd)
		return (1);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
