#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdio.h>

void	fn_echo(char **ag, size_t len)
{
	size_t	i;
	int		flag;

	flag = 0;
	if (!ft_strcmp("-n", ag[1]))
		flag++;
	i = 1;
	while (ag[i])
	{
		if ((flag && i > 1) || !flag)
		{
			printf("%s", ag[i]);
			if (i < len - 1)
				printf(" ");
		}
		i++;
	}
	if (!flag)
		printf("\n");
}
