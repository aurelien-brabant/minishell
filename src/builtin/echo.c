#include <stdio.h>

#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"

int	builtin_echo(int argc, char *argv[])
{
	int		i;
	int		flargv;

	if (!argv[1])
		return (0);
	flargv = 0;
	if (!ft_strcmp("-n", argv[1]))
		flargv++;
	i = 1;
	while (i < argc)
	{
		if ((flargv && i > 1) || !flargv)
		{
			printf("%s", argv[i]);
			if (i < argc - 1)
				printf(" ");
		}
		i++;
	}
	if (!flargv)
		printf("\n");
	return (0);
}
