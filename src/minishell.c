#include <stdlib.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "minishell/parser.h"

/*
** Invoke a minishell instance.
*/

int	minishell_invoke(unsigned int opt, char **optargs, char **envp)
{
	char	*cmd;
	char	**env;
	t_vector	parsed;

	stat_init(opt, optargs);
	env = get_env(envp);
	if (!env)
		return (1);
	if (opt & (1 << OPTION_TYPE_COMMAND))
	{
		parser_invoke(optargs[OPTION_TYPE_COMMAND]);
		return (0);
	}
	while (1)
	{
		cmd = prompt_present("\033[0;33mminishell\033[0m-1.0$ ");
		parsed = parser_invoke(cmd);
		exec(parsed, &env);
		ft_gc_wipe(stat_get()->tmp_gc);
	}
	ft_gc_destroy(stat_get()->tmp_gc);
	stat_destroy();
	return (0);
}
