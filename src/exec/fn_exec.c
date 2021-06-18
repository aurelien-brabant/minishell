#include "minishell/minishell.h"
#include "minishell/exec.h"
#include "minishell/env.h"
#include "minishell/stat.h"
#include "minishell/signal.h"
//#include "minishell/stat.h"
#include "libft/cstring.h"
#include "libft/io.h"
//#include "libft/vector.h"
//#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
//#include <stdio.h>

static char	**get_path(char *cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	path = minishell_getenv("PATH");
	if (path == NULL)
	{
		ft_dprintf(STDERR_FILENO, "WTF, path not set?");
		return (NULL);
	}
//	paths = ft_gc_add(stat_get()->tmp_gc, ft_split(path, ':'), &free_tab);
	paths = ft_split(path, ':');
	if (!paths)
	{
		free(path);
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		//paths[i] = ft_gc_add(stat_get()->tmp_gc, ft_strjoin(tmp, cmd), &free);
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		i++;
	}
	return (paths);
}

static char	**add_cmd_to_path(char *cmd, char **path)
{
	char	**final_path;
	int		size;
	int		i;

	size = tab_len(path);
	final_path = (char **)malloc(sizeof(char *) * (size + 2));
	if (!final_path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		final_path[i] = ft_strdup(path[i]);
		i++;
	}
	final_path[i] = ft_strdup(cmd);
	final_path[i + 1] = NULL;
	return (final_path);
}

static void	run_exec(char **path, char **ag)
{
	int		ret;
	int		i;
	struct stat	buffer;

	ret = 0;
	i = 0;
	sig_pid = fork();
	if (!sig_pid)
	{
		while (path[i])
		{
			if (!stat(path[i], &buffer))
				execve(path[i], ag, stat_get()->env->args);
			i++;
		}
		ft_dprintf(2, "minishell: %s: command not found\n", ag[0]);
		exit(127);
	}
	waitpid(sig_pid, &ret, 0);
/*	while (path[i])
	{
		pid = fork();
		if (pid == 0)
			exit(execve(path[i], ag, stat_get()->env->args));
		waitpid(pid, &ret, 0);
		if (WEXITSTATUS(ret) != 255)
			break ;
		if (!stat(path[i], &buffer))
		{
			//childpid = fork();
			sig_pid = fork();
			if (sig_pid == 0)
				execve(path[i], ag, stat_get()->env->args);
		//	else
		//	{
				//waitpid(childpid, &ret, 0);
			waitpid(sig_pid, &ret, 0);
			if (WEXITSTATUS(ret) != 255)
				break ;
		//	}
//			ft_dprintf(2, "minishell: %s: command not found\n", ag[0]);
		}
		i++;
	}
	if (WEXITSTATUS(ret) == 255)
		ft_dprintf(2, "minishell: %s: command not found\n", ag[0]);*/
}

void	fn_exec(char *cmd, char **ag)
{
	char	**tmp;
	char	**path;

	tmp = get_path(cmd);
	if (!tmp)
		return ;
	path = add_cmd_to_path(cmd, tmp);
	free_tab(tmp);
	if (!path)
		return ;
	run_exec(path, ag);
	free_tab(path);
}
