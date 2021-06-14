#include "minishell/minishell.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*get_env_value(const char *var, char **env)
{
	char	*value;
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], size))
		{
			value = ft_strdup(env[i] + size);
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

static void	update_pwd(char *old_pwd, char ***env, size_t len)
{
	char	*tmp;
	char	**new_pwd;

	new_pwd = (char **)malloc(sizeof(char *) * 3);
	if (!new_pwd)
		return ;
	tmp = ft_strdup(get_pwd());
	new_pwd[0] = ft_strdup("export");
	new_pwd[1] = ft_strjoin("PWD=", tmp);
	new_pwd[2] = NULL;
	fn_export(new_pwd, env, len);
	free(tmp);
	free(new_pwd[1]);
	new_pwd[1] = ft_strjoin("OLDPWD=", old_pwd);
	fn_export(new_pwd, env, len);
	free_tab(new_pwd);
}

/* Modifier ret pour checker si un dossier n'existe pas ou si c'est un nom de fichier qui existe par exemple... */

void	fn_cd(char **ag, char ***env, size_t len)
{
	char	*goto_path;
	char	*old_pwd;
	int		ret;

	old_pwd = ft_strdup(get_pwd());
	if (ag[1])
		goto_path = ag[1];
	else
	{
		goto_path = get_env_value("HOME=", *env);
		if (!goto_path)
			ft_dprintf(2, "cd: HOME not set\n");
	}
	if (!goto_path)
		return ;
	ret = chdir(goto_path);
	printf("ret{%d]\n", ret);
	if (!ret)
		update_pwd(old_pwd, env, len);
	else
		ft_dprintf(2, "cd: aucun fichier ou dossier de ce type: %s\n", goto_path);
	free(old_pwd);
}
