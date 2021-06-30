#include <stdlib.h>

#include "minishell/env.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"
#include "libft/io.h"

int	builtin_unset(int argc, char *argv[], bool forked)
{
	char	*s;
	char	*sep;

	(void)forked;
	if (argc == 2)
	{
		s = ft_strdup(argv[1]);
		sep = ft_strchr(s, '=');
		if (sep != NULL)
			*sep = '\0';
		if (argv[1][0] == '=' || !is_valid_env_var_name(argv[1]))
		{
			ft_dprintf(2, "minishell: unset \"%s\": not a valid"
				" identifier\n", argv[1]);
			return (1);
		}
		else
			minishell_unsetenv(s);
		free(s);
	}
	return (0);
}
