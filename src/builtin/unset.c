#include <stdlib.h>

#include "minishell/env.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"

int	builtin_unset(int argc, char *argv[])
{
	char	*s;
	char	*sep;

	if (argc == 2)
	{
		s = ft_strdup(argv[1]);
		sep = ft_strchr(s, '=');
		if (sep != NULL)
			*sep = '\0';
		minishell_unsetenv(s);
		free(s);
	}
	return (0);
}
