#include <stdlib.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "minishell/parser.h"

/*
** Invoke a minishell instance.
*/

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(data));
	if (!data)
		return (NULL);
	data->env = get_env(envp);
	return (data);
}

int	minishell_invoke(unsigned int opt, char **optargs, char **envp)
{
	char	*cmd;
	t_data	*data;

	stat_init(opt, optargs);
	data = init_data(envp);
	if (opt & (1 << OPTION_TYPE_COMMAND))
	{
		parser_invoke(optargs[OPTION_TYPE_COMMAND]);
		return (0);
	}
	while (1)
	{
		cmd = prompt_present("\033[0;33mminishell\033[0m-1.0$ ");
		parser_invoke(cmd);
		//exec(cmd, envp);
		exec(cmd, data);
		ft_gc_wipe(stat_get()->tmp_gc);
	}
	ft_gc_destroy(stat_get()->tmp_gc);
	stat_destroy();
	return (0);
}
