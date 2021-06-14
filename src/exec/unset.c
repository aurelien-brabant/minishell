#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdlib.h>

static char	**create_unset_env(int to_del, char **env)
{
	int		i;
	int		j;
	char	**new_env;
	int		size;
	
	i = 0;
	j = 0;
	size = tab_len(env);
	new_env = (char **)malloc(sizeof(char *) * size);
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (i != to_del)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static char	**unset_var(char *var, char **env)
{
	int		i;
	int		to_del;

	i = 0;
	to_del = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
		{
			to_del = i;
			break ;
		}
		i++;
	}
	if (to_del)
		return (create_unset_env(to_del, env));
	return (env);
}

void	fn_unset(char **ag, char ***env, size_t len)
{
	char	**new_env;
	char	*var;

	if (len == 2)
	{
		var = ft_strdup(ag[1]);
		new_env = unset_var(var, *env);
		free(var);
		if (!new_env)
			return ;
		*env = new_env;
	}
}
