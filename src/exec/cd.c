#include "minishell/minishell.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void	update_pwd(char *old_pwd, char ***env)
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
	goto_path = ft_strdup(cmd + 3);
	ret = chdir(goto_path);
	printf("ret_cd [%d]\n", ret);
	if (!ret)
		update_pwd(old_pwd, env);
	else
		ft_dprintf(2, "cd: aucun fichier ou dossier de ce type: %s\n", goto_path);
	free(goto_path);
	free(old_pwd);
}
