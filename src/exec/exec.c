#include "minishell/exec.h"
#include "libft/cstring.h"
//#include <signal.h>
//#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*concatenate_path(char **envp, char *cmd)
{
	char	*path;

	(void)envp;
	path = "/bin/";
	path = ft_strjoin(path, cmd);
	return (path);
}

char	*find_path(char **envp)
{
	int	i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp("PATH=", envp[i]))
		{
			path = (char *)malloc(sizeof(char) * (ft_strlen(envp[i] + 5) + 1));
			path = ft_strdup(envp[i] + 5);
			printf("%s\n", path);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*paths;

	paths = find_path(env);
	path = ft_strjoin(paths, cmd);
	return (path);
}

void	fn_exec(char *cmd, char **envp)
{
	char **env;
	char *path;
	//int		ret;

	env = get_env(envp);
	if (!env)
		return ;
	path = get_path(cmd, env);
	if (!path)
		return ;
	printf("path [%s]\n", path);
	//ret = execve(cmd, path, env);
	//printf("ret_execve [%d]\n", ret);
}

void	exec(char *cmd, char **envp)
{
	//int	sig;
	//int	pid;

	//pid = waitpid(-1, &sig, 0);
	if (!ft_strcmp(cmd, "env"))
		fn_env(envp);
	else if (!ft_strncmp(cmd, "echo", 4))
		fn_echo(cmd + 5);
	else if (!ft_strcmp(cmd, "exit"))
		fn_exit();
	else
		fn_exec(cmd, envp);
	//else
	//	printf("minishell: %s: command not found\n", cmd);
	//printf("sig [%d]\npid [%d]\n", sig, pid);
}
