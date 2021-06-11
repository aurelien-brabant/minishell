#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdio.h>

void	fn_pwd(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			printf("%s\n", env[i] + 4);
		i++;
	}
	return ;
}
