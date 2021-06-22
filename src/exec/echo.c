#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdio.h>

void	fn_echo(char **cmd, size_t len)
{
	size_t	i;
	int		flag;

	if (!cmd[1])
		return ;
	flag = 0;
	if (!ft_strcmp("-n", cmd[1]))
		flag++;
	i = 1;
	while (i < len)
	{
		if ((flag && i > 1) || !flag)
		{
			printf("%s", cmd[i]);
			if (i < len - 1)
				printf(" ");
		}
		i++;
	}
	if (!flag)
		printf("\n");
}
