#include <unistd.h>
#include <stdlib.h>

#include "minishell/minishell.h"
#include "minishell/error.h"

#include "libft/ctype.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include "libft/core.h"

/*
** Check if name is a valid environment variable name. 
** A valid variable name is any name composed of letters from the portable 
** character set, digits, and underscores ('_').
** - Lowercase and uppercase letters can be mixed up,
** even if it is not advisable.
** - The name CAN contain digits but CAN'T start with one.
**
** REFERENCE: https://pubs.opengroup.org/onlinepubs/9699919799/
*/

bool	is_valid_env_var_name(const char *name)
{
	if (ft_isdigit(*name))
		return (false);
	while (*name != '\0')
	{
		if (*name != '_' && !ft_isalnum(*name))
			return (false);
		++name;
	}
	return (true);
}

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

char	*minishell_getenv(const char *name)
{
	t_stringv	*env;
	size_t		i;
	size_t		name_len;

	if (!is_valid_env_var_name(name))
		return (NULL);
	env = g_msh.env;
	name_len = ft_strlen(name);
	i = 0;
	while (env->data[i] != NULL)
	{
		if (ft_strncmp(env->data[i], name, name_len) == 0
			&& *(env->data[i] + name_len) == '=')
		{
			return (env->data[i] + name_len + 1);
		}
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

void	minishell_setenv(const char *name, char *value)
{
	t_stringv	*env;
	char		*entry;
	size_t		i;
	size_t		name_len;
	size_t		value_len;

	i = 0;
	env = g_msh.env;
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	entry = gc_add_global(ft_calloc(name_len + value_len + 2,
				sizeof (*entry)), &free);
	ft_strlcat(entry, name, name_len + 1);
	ft_strlcat(entry, "=", name_len + 2);
	ft_strlcat(entry, value, name_len + value_len + 2);
	while (env->data[i] != NULL)
	{
		if (ft_strncmp(env->data[i], name, name_len) == 0)
		{
			env->data[i] = entry;
			return ;
		}
		++i;
	}
	stringv_add(env, entry);
}

/*
** Unset the environement variable which name is provided as the single
** argument of this function. Unsetting an environment variable basically
** means removing it from the environment. If the environment variable is not
** set, nothing will happen.
*/

void	minishell_unsetenv(char *var_name)
{
	t_stringv	*env;
	size_t		i;
	size_t		var_name_len;

	env = g_msh.env;
	var_name_len = ft_strlen(var_name);
	i = 0;
	while (env->data[i] != NULL)
	{
		if (ft_strncmp(env->data[i], var_name, var_name_len) == 0)
		{
			stringv_del(env, i);
			return ;
		}
		++i;
	}
}

void	minishell_printenv(void)
{
	t_stringv	*env;
	size_t		i;

	env = g_msh.env;
	i = 0;
	while (env->data[i] != NULL)
	{
		ft_putstr_fd(env->data[i++], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
