#include "minishell/minishell.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*get_home_value(char *var, char **env)
{
	char	*value;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], 5))
		{
			size = ft_strlen(env[i]) - 5;
			value = (char *)malloc(sizeof(char) * (size + 1));
			if (!value)
				return (NULL);
			value = ft_strdup(env[i] + 5);
			return (value);
		}
		i++;
	}
	return (NULL);
}

static void	update_pwd(char *old_pwd, char ***env)
{
	char	*new_pwd;
	char	*tmp;

	tmp = ft_strdup(get_pwd());
	new_pwd = ft_strjoin("export PWD=", tmp);
	free(tmp);
	fn_export(new_pwd, env);
	free(new_pwd);
	tmp = ft_strjoin("export OLDPWD=", old_pwd);
	fn_export(tmp, env);
	free(tmp);
}

/* Modifier ret pour checker si un dossier n'existe pas ou si c'est un nom de fichier qui existe par exemple... */

void	fn_cd(char *cmd, char ***env)
{
	char	*goto_path;
	char	*old_pwd;
	int		ret;

	old_pwd = ft_strdup(get_pwd());
	if (cmd[2])
		goto_path = ft_strdup(cmd + 3);
	else
	{
		goto_path = get_home_value("HOME=", *env);
		if (!goto_path)
			ft_dprintf(2, "cd: HOME not set\n");
	}
	if (!goto_path)
		return ;
	ret = chdir(goto_path);
	//printf("ret_cd [%d]\n", ret);
	if (!ret)
		update_pwd(old_pwd, env);
	else
		ft_dprintf(2, "cd: aucun fichier ou dossier de ce type: %s\n", goto_path);
	free(goto_path);
	free(old_pwd);
}
