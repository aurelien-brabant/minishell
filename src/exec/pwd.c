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

void	fn_pwd(void)
{
	char	*pwd;

	pwd = ft_strdup(get_pwd());
	if (!pwd)
		return ;
	printf("%s\n", pwd);
	free(pwd);
}
