#include "minishell/exec.h"
#include "libft/cstring.h"

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

void	echo(char *s)
{
	printf("%s\n", s);
}

void	exec(char *cmd, char **envp)
{
	if (!ft_strcmp(cmd, "env"))
		print_tab(envp);
	else if (!ft_strncmp(cmd, "echo", 4))
		echo(cmd + 5);
	else if (!ft_strcmp(cmd, "exit"))
	{
		printf("exit\n");
		exit (0);
	}
	else
		printf("minishell: %s: command not found\n", cmd);
}
