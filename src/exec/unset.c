#include "minishell/minishell.h"
#include "minishell/env.h"
#include "libft/cstring.h"
#include <stdlib.h>

void	fn_unset(char **cmd, size_t len)
{
	char	*s;
	char	*sep;

	if (len == 2)
	{
		s = ft_strdup(cmd[1]);
		sep = ft_strchr(s, '=');
		if (sep != NULL)
			*sep = '\0';
		minishell_unsetenv(s);
		free(s);
	}
}
