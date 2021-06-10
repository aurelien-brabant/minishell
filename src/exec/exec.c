#include "minishell/exec.h"
#include "libft/cstring.h"
//#include <signal.h>
//#include <sys/wait.h>
#include <unistd.h>

void	print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	echo(char *s)
{
	return (printf("%s\n", s));
}

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

	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp("PATH=", envp[i]))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char **envp, char *cmd)
{
	char	*path;
	char	*paths;

	printf("1");
	paths = find_path(envp);
	printf("2");
	path = ft_strjoin(paths, cmd);
	printf("3");
	return (path);
}

void	exec(char *cmd, char **envp)
{
	//int	sig;
	//int	pid;
	char	*path;

	//pid = waitpid(-1, &sig, 0);
	if (!ft_strcmp(cmd, "env"))
		print_tab(envp);
	else if (!ft_strncmp(cmd, "echo", 4))
		echo(cmd + 5);
	else if (!ft_strcmp(cmd, "exit"))
	{
		printf("exit\n");
		exit (0);
	}
	else if (!ft_strcmp(cmd, "ls"))
	{
		path = get_path(envp, cmd);
		printf("%s\n", path);
		execve(path, NULL, envp);
		free(path);
	}
	else
		printf("minishell: %s: command not found\n", cmd);
	//printf("sig [%d]\npid [%d]\n", sig, pid);
}
