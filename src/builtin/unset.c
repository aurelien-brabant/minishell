#include <stdlib.h>

#include "minishell/env.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"
#include "libft/io.h"

int	builtin_unset(int argc, char *argv[], bool forked)
{
	(void)forked;
	if (argc == 2)
	{
		if (argv[1][0] == '=' || !is_valid_env_var_name(argv[1]))
		{
			ft_dprintf(2, "minishell: unset \"%s\": not a valid"
				" identifier\n", argv[1]);
			return (1);
		}
		else
			minishell_unsetenv(argv[1]);
	}
	return (0);
}
