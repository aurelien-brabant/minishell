#include "minishell/minishell.h"
#include <stdio.h>

void	fn_echo(char *s)
{
	if (s[0] == '-' && s[1] == 'n')
		printf("%s", s + 3);
	else
		printf("%s\n", s);
}
