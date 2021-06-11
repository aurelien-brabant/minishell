#include "minishell/exec.h"
#include "libft/cstring.h"
//#include <signal.h>
//#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
static void	print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}

}
*/

static char	*find_env_path(char **env)
{
	int	i;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			path = (char *)malloc(sizeof(char) * (ft_strlen(env[i] + 5) + 1));
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
	int		i;

	(void)cmd;
	path = find_env_path(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		i++;
	}
	return (paths);
}

static void	fn_exec(char *cmd, char **envp)
{
	char	**env;
	char	**path;
	int		ret;
	int		i;
	char	**args;

	/* juste pour tester car on n'a pas fini le parsing... */
	args = malloc(sizeof(char *) * 2);
	args[0] = ft_strdup(cmd);
	args[1] = NULL;
	/* à la place d'args on aura les arguments donnés après la commande lors du parsing */

	env = get_env(envp);
	if (!env)
		return ;
	path = get_path(cmd, env);
	if (!path)
		return ;
	i = -1;
	ret = 0;
	while (path[i++] || ret != -1)
		ret = execve(path[i], args, env);
	printf("minishell: %s: command not found\n", cmd);
	
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
	//printf("sig [%d]\npid [%d]\n", sig, pid);
}
