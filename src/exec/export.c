#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdlib.h>

static char	**create_export_env(char *var, char **env)
{
	char	**new_env;
	int		i;
	int		size;

	size = tab_len(env);
	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	return (new_env);
}
/*
static char	*get_env_value(char *var)
{
	char	*value;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			size = ft_strlen(var + i);
			break ;
		}
		i++;
	}
	value = (char *)malloc(sizeof(char) * (size + 1));
	if (!value)
		return (NULL);
	value = ft_strdup(var + i);
	return (value);
}
*/

static int	existing_var(char *var, char **env)
{
	int		i;
	int		var_size;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	var_size = i;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, var_size))
			return (i);
		i++;
	}
	return (0);
}

static char	**export_env(char *var, char **env)
{
	int		index;

	index = existing_var(var, env);
	if (!index)
		return (create_export_env(var, env));
	free(env[index]);
	env[index] = ft_strdup(var);
	return (env);
}

void	fn_export(char *cmd, char **env)
{
	char	*var;
	char	**new_env;

	var = ft_strdup(cmd + 7);
	if (!var)
		return ;
	new_env = export_env(var, env);
	free(var);
	if (!new_env)
		return ;
	print_tab(new_env);
}
