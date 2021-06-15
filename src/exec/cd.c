#include <limits.h>

#include "minishell/minishell.h"
#include "minishell/env.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
//#include <stdio.h>

static void	update_pwd(char *old_pwd)
{
	char	new_pwd[PATH_MAX];

	/* We can use a stack buffer here, no need to ask for malloc
	getcwd(new_pwd, PATH_MAX); 
	*/
	minishell_setenv("PWD", new_pwd);
	minishell_setenv("OLDPWD", old_pwd);
}

/* Modifier ret pour checker si un dossier n'existe pas ou si c'est un nom de fichier qui existe par exemple... */

void	fn_cd(char **ag)
{
	char	*goto_path;
	char	old_pwd[PATH_MAX];
	int		ret;

	getcwd(old_pwd, PATH_MAX);
	if (ag[1])
		goto_path = ag[1];
	else
	{
		goto_path = minishell_getenv("HOME");
		if (!goto_path)
			ft_dprintf(2, "cd: HOME not set\n");
	}
	if (!goto_path)
		return ;
	ret = chdir(goto_path);
	//printf("ret[%d]\n", ret);
	if (!ret)
		update_pwd(old_pwd);
	else
		ft_dprintf(2, "cd: aucun fichier ou dossier de ce type: %s\n", goto_path);
	free(old_pwd);
}
