#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdlib.h>
#include <stdio.h>

static size_t	tab_len(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static char	**create_new_env(int to_del, char **env)
{
	int		i;
	int		j;
	char	**new_env;
	size_t	size;
	
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

char	**unset_var(char *var, char **env)
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
		return (create_new_env(to_del, env));
	return (env);
}

void	fn_unset(char *cmd, char **env)
{
	char	**new_env;
	char	*var;

	var = ft_strdup(cmd + 6);
	new_env = unset_var(var, env);
	free(var);
	if (!new_env)
		return ;
	print_tab(new_env);
}
