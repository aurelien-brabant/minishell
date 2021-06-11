#include "minishell/exec.h"
#include "minishell/stat.h"
#include "libft/cstring.h"
#include "libft/io.h"
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
	paths = ft_gc_add(stat_get()->tmp_gc, ft_split(path, ':'), &free_tab);
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

static void	fn_exec(char *cmd, t_data *data)
{
//	char	**env;
	char	**path;
	int		ret;
	int		i;
	char	**args;
	int		pid;

	/* juste pour tester car on n'a pas fini le parsing... */
	args = malloc(sizeof(char *) * 2);
	args[0] = ft_strdup(cmd);
	args[1] = NULL;
	/* à la place d'args on aura les arguments donnés après la commande lors du parsing */
//	env = get_env(envp);
//	if (!env)
//		return ;
	path = get_path(cmd, data->env);
	if (!path)
		return ;
	i = -1;
	ret = 0;
	while (path[i++])
	{
		pid = fork();
		if (pid == 0)
			exit(execve(path[i], args, data->env));
		waitpid(pid, &ret, 0);
		if (WEXITSTATUS(ret) != 255)
			break ;
	}
	if (WEXITSTATUS(ret) == 255)
		ft_dprintf(2, "minishell: %s: command not found\n", cmd);
//	free_tab(env);
}

void	exec(char *cmd, t_data *data)
{
//	char	**env;

//	env = get_env(envp);
//	if (!env)
//		return ;
	if (!ft_strncmp(cmd, "echo", 4))
		fn_echo(cmd + 5);
	else if (!ft_strncmp(cmd, "cd", 2))
		fn_cd(data->env);
	else if (!ft_strcmp(cmd, "pwd"))
		fn_pwd(data->env);
	else if (!ft_strncmp(cmd, "export", 6))
		fn_export(cmd, data->env);
	else if (!ft_strncmp(cmd, "unset", 5))
		fn_unset(cmd, data->env);
	else if (!ft_strcmp(cmd, "env"))
		print_tab(data->env);
	else if (!ft_strcmp(cmd, "exit"))
		fn_exit();
	else
		fn_exec(cmd, data);
	//free_tab(data->env);
}
