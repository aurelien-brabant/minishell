#include "minishell/minishell.h"
//#include "minishell/stat.h"
//#include "libft/io.h"
#include "libft/cstring.h"
#include <stdlib.h>

char	**get_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
//	env = ft_gc_add(stat_get()->tmp_gc, malloc(sizeof(char *) * (i + 1)), &free_tab);
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
//		env[i] = ft_gc_add(stat_get()->tmp_gc, ft_strdup(envp[i]), &free);
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

