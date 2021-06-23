#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

char	*get_pwd(void)
{
	char	buf[PATH_MAX];

	return (getcwd(buf, PATH_MAX));
}

int	fn_pwd(char *argv[], size_t argc)
{
	char	*pwd;

	(void)argv;
	(void)argc;
	pwd = ft_strdup(get_pwd());
	if (!pwd)
		return (0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
