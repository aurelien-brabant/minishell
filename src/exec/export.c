#include "minishell/minishell.h"
#include "minishell/env.h"
#include "libft/cstring.h"
#include "libft/ctype.h"
#include <stdlib.h>
#include "libft/io.h"

static int	check_var_name(char *s)
{
	int		i;

	i = 0;
	if (ft_isdigit(s[0]))
		return (0);
	while (s[i])
	{
//		if (ft_isdigit(s[i]) || ft_isupper(s[i]) || s[i] == '_')
		if (ft_isdigit(s[i]) || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	fn_export(char **ag, size_t len)
{
	char	*var_name;
	char	*s;

	if (len == 2)
	{
		s = ft_strdup(ag[1]);
		var_name = s;
		s = ft_strchr(s, '=');
		if (s == NULL)
			s = "";
		else
			*s++ = '\0';
		if (check_var_name(var_name))
			minishell_setenv(var_name, s);
		else
			ft_dprintf(2, "minishel: export \"%s\" : identifiant non valable\n", var_name);
		free(var_name);
	}
}

/*
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
//	free(env[index]);
	env[index] = ft_strdup(var);
	return (env);
}

void	fn_export(char **ag, char ***env, size_t len)
{
	char	*var;
	char	**new_env;

	if (len == 2)
	{
		var = ft_strdup(ag[1]);
		if (!var)
			return ;
		new_env = export_env(var, *env);
		free(var);
		if (!new_env)
			return ;
		*env = new_env;
	}
}
*/

