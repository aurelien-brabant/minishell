#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <unistd.h>
#include <stdlib.h>

static char	*get_env_pwd(char **env)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			pwd = ft_strdup(env[i] + 4);
		i++;
	}
	return (pwd);
}

void	fn_cd(char *cmd, char ***env)
{
	char	*path;
	char	*new_pwd;
	char	*old_pwd;
	char	*pwd;

	pwd = get_env_pwd(*env);
	path = ft_strdup(cmd + 3);
	chdir(path);
	new_pwd = ft_strjoin("export PWD=", path);
	free(path);
	fn_export(new_pwd, env);
	free(new_pwd);
	old_pwd = ft_strjoin("export OLDPWD=", pwd);
	free(pwd);
	fn_export(old_pwd, env);
	free(old_pwd);
}
