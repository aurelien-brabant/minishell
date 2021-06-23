#include <limits.h>
#include <unistd.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <string.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/builtin.h"
#include "minishell/env.h"

static void	update_pwd(char *old_pwd)
{
	char	new_pwd[PATH_MAX];

	minishell_setenv("PWD", new_pwd);
	minishell_setenv("OLDPWD", old_pwd);
}

int	builtin_cd(int argc, char *argv[])
{
	char	*goto_path;
	char	old_pwd[PATH_MAX];
	int		ret;

	(void)argc;
	getcwd(old_pwd, PATH_MAX);
	if (argv[1])
		goto_path = argv[1];
	else
	{
		goto_path = minishell_getenv("HOME");
		if (!goto_path)
			ft_dprintf(2, "cd: HOME not set\n");
		return (1);
	}
	if (!goto_path)
		return (0);
	ret = chdir(goto_path);
	if (!ret)
		update_pwd(old_pwd);
	else
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", goto_path, strerror(errno));
		return (2);
	}
	return (0);
}
