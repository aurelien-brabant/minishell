#include "minishell/exec.h"
//#include "minishell/stat.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include "libft/vector.h"
//#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*find_env_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
	//		path = ft_gc_add(stat_get()->tmp_gc, ft_strdup(env[i] + 5), &free);
			path = ft_strdup(env[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	**get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	(void)cmd;
	path = find_env_path(env);
	if (!path)
		return (NULL);
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
	free(path);
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

static void	run_exec(char **path, char **ag, char ***env)
{
	int		ret;
	int		pid;
	int		i;

	ret = 0;
	i = 0;
	while (path[i])
	{
		pid = fork();
		if (pid == 0)
			exit(execve(path[i], ag, *env));
		waitpid(pid, &ret, 0);
		if (WEXITSTATUS(ret) != 255)
			break ;
		i++;
	}
	if (WEXITSTATUS(ret) == 255)
		ft_dprintf(2, "minishell: %s: command not found\n", ag[0]);
}

static void	fn_exec(char *cmd, char **ag, char ***env)
{
	char	**tmp;
	char	**path;

	tmp = get_path(cmd, *env);
	if (!tmp)
		return ;
	path = add_cmd_to_path(cmd, tmp);
	free_tab(tmp);
	if (!path)
		return ;
	run_exec(path, ag, env);
	free_tab(path);
}

void	exec(t_vector parsed, char ***env)
{
	t_command	*argvs;
	char	*cmd;
	char	**ag;
	size_t	len;
	//size_t	length;
	size_t	i;

	//length = ft_vector_length(parsed);
	i = 0;
//	while (i < length)
//	{
		argvs = ft_vector_get(parsed, i);
		ag = (char **)argvs->argv->args;
		cmd = ag[0];
		len = argvs->argv->length;
		if (!ft_strcmp(cmd, "echo"))
			fn_echo(ag, len);
		else if (!ft_strcmp(cmd, "cd"))
			fn_cd(ag, env, len);
		else if (!ft_strcmp(cmd, "pwd"))
			fn_pwd();
		else if (!ft_strcmp(cmd, "export"))
			fn_export(ag, env, len);
		else if (!ft_strcmp(cmd, "unset"))
			fn_unset(ag, env, len);
		else if (!ft_strcmp(cmd, "env"))
			print_tab(*env);
		else if (!ft_strcmp(cmd, "exit"))
			fn_exit();
		else
			fn_exec(cmd, ag, env);
//		i++;
//	}
}
