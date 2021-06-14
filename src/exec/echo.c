#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdio.h>

void	fn_echo(char **ag, size_t len)
{
	size_t	i;
	int		flag;

	i = 1;
	flag = 0;
	if (!ft_strcmp("-n", ag[1]))
		flag++;
	while (ag[i])
	{
		printf("%s", ag[i]);
		if (i < len)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
