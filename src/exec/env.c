#include "minishell/minishell.h"
#include "libft/cstring.h"
#include <stdio.h>
#include <stdlib.h>

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

char	**get_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	fn_env(char **envp)
{
	char	**env;

	env = get_env(envp);
	if (!env)
		return ;
	print_tab(env);
}
