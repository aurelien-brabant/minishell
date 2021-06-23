#include <unistd.h>

#include "libft/cstring.h"

#include "minishell/stat.h"
#include "minishell/builtin.h"

int	builtin_env(int argc, char *argv[])
{
	t_argv	*env;
	size_t	i;

	(void)argv;
	(void)argc;
	env = stat_get()->env;
	i = 0;
	while (i < env->length)
	{
		write(STDOUT_FILENO, env->args[i], ft_strlen(env->args[i]));
		write(STDOUT_FILENO, "\n", 1);
		++i;
	}
	return (0);
}
