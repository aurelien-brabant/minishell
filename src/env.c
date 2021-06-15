#include <unistd.h>

#include "minishell/minishell.h"
#include "minishell/stat.h"
//#include "minishell/stat.h"
#include "libft/io.h"
#include "libft/cstring.h"
#include "libft/core.h"
#include <stdlib.h>

/*
** Because we do not have access to setenv or putenv, we need
** to use our own environment based on the copy we received
** when the original shell forked minishell.
** Therefore a special getenv function is needed.
**
** var_name is the name of the environment variable. Such name
** should only contain alphanumeric characters. No dollar or equal
** sign must be present.
**
** The VALUE of the environment variable is returned (i.e the character sequence
** immediately following the equal sign in the environment). The returned string
** is NOT guaranteed to be modifiable, therefore if it is needed a call to
** ft_strdup must be performed.
**
** NULL is returned if the variable could not be found.
**
** Example: minishell_getenv("HOME") => /home/abrabant
*/

char *minishell_getenv(char *var_name)
{
	t_argv	*env;
	size_t	i;
	size_t	var_name_len;

	env = stat_get()->env;
	var_name_len = ft_strlen(var_name);
	i = 0;
	while (env->args[i] != NULL)
	{
		if (ft_strncmp(env->args[i], var_name, var_name_len) == 0)
			return (env->args[i] + var_name_len + 1);
		++i;
	}
	return (NULL);
}

/*
** Set the environment variable which name is var_name.
**
** If the variable is already set, the old value is replaced by the new one.
** Otherwise, the new variable is appended to the environment.
*/

void minishell_setenv(char *var_name, char *value)
{
	t_argv	*env;
	char	*entry;
	size_t	i;
	size_t	var_name_len;
	size_t	value_len;

	i = 0;
	env = stat_get()->env;
	var_name_len = ft_strlen(var_name);
	value_len = ft_strlen(value);
	entry = ft_gc_add(stat_get()->global_gc,
			ft_calloc(var_name_len + value_len + 2, sizeof (*entry)), &free);
	ft_strlcat(entry, var_name, var_name_len + 1);
	ft_strlcat(entry, "=", var_name_len + 2);
	ft_strlcat(entry, value, var_name_len + value_len + 2);
	while (env->args[i] != NULL)
	{
		if (ft_strncmp(env->args[i], var_name, var_name_len) == 0)
		{
				env->args[i] = entry;
				return ;
		}
		++i;
	}
	env->args[i] = entry;
	argv_append(env, NULL);
}

/*
** Unset the environement variable which name is provided as the single
** argument of this function. Unsetting an environment variable basically
** means removing it from the environment. If the environment variable is not
** set, nothing will happen.
*/

void	minishell_unsetenv(char *var_name)
{
	t_argv	*env;
	size_t	i;
	size_t	var_name_len;

	env = stat_get()->env;
	var_name_len = ft_strlen(var_name);
	i = 0;
	while (env->args[i] != NULL)
	{
		if (ft_strncmp(env->args[i], var_name, var_name_len) == 0)
		{
			argv_remove(env, i);
			return ;
		}
		++i;
	}
}

void	minishell_printenv(void)
{
	t_argv	*env;
	size_t	i;

	env = stat_get()->env;
	i = 0;
	while (env->args[i] != NULL)
	{
		ft_putstr_fd(env->args[i++], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

/* LEGACY CODE */

/*
char	*get_env_value(const char *var, char **env)
{
	char	*value;
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(var, env[i], size) == 0)
		{
			value = ft_strdup(env[i] + size + 1);
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

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
*/

