#include "minishell/minishell.h"
#include "minishell/exec.h"
#include "minishell/env.h"
#include "minishell/stat.h"
#include "minishell/signal.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

static char	**join_path(char **paths, char *bin)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, bin);
		free(tmp);
		i++;
	}
	return (paths);
}

static char	**get_path(char *bin)
{
	char	**paths;
	char	*path;

	path = minishell_getenv("PATH");
	if (path == NULL)
	{
		ft_dprintf(STDERR_FILENO, "minishell: PATH not set\n");
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (!paths)
	{
		free(path);
		return (NULL);
	}
	return (join_path(paths, bin));
}

void	fn_exec(char **cmd)
{
	char	**path;
	struct stat	buffer;
	int		i;

	if (!stat(cmd[0], &buffer))
		exit(execve(cmd[0], cmd, stat_get()->env->args));
	path = get_path(cmd[0]);
	if (!path)
		exit(127);
	i = 0;
	while (path[i])
	{
		if (!stat(path[i], &buffer))
			exit(execve(path[i], cmd, stat_get()->env->args));
		i++;
	}
	free_tab(path);
	ft_dprintf(2, "minishell: %s: command not found\n", cmd[0]);
	exit(127);
}
