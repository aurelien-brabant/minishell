#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

#include "libft/io.h"
#include "libft/cstring.h"

#include "minishell/minishell.h"
#include "minishell/constants.h"

t_minishell_data	g_msh = {
	.pids = NULL,
	.status = 0,
};

static void	msh_data_init(char **envp)
{
	g_msh.gc_glob = ft_gc_new();
	g_msh.gc_tmp = ft_gc_new();
	g_msh.env = stringv_new(70);
	while (*envp != NULL)
		stringv_add(g_msh.env, *envp++);
}

static int	minishell_non_interactive(char **optargs)
{
	t_pipeline	*pipeline;

	pipeline = parser_invoke(optargs[OPTION_TYPE_COMMAND]);
	if (pipeline != NULL)
		exec(pipeline);
	return (0);
}

int	minishell_invoke(unsigned int opt, char **optargs, char **envp)
{
	char		*cmd;
	t_pipeline	*pipeline;

	msh_data_init(envp);
	if (opt & (1 << OPTION_TYPE_COMMAND))
		return (minishell_non_interactive(optargs));
	while (1)
	{
		cmd = prompt_present();
		if (cmd == NULL)
			break ;
		pipeline = parser_invoke(cmd);
		if (pipeline != NULL)
			exec(pipeline);
		else
			g_msh.status = PARSING_ERROR;
		ft_gc_wipe(g_msh.gc_tmp);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	unlink(HERE_DOC_FILEPATH);
	minishell_exit(EXIT_SUCCESS);
	return (0);
}

/* rl_clear_history(); ? */

void	minishell_exit(int exit_status)
{
	ft_gc_destroy(g_msh.gc_tmp);
	ft_gc_destroy(g_msh.gc_glob);
	stringv_destroy(g_msh.env);
	exit(exit_status);
}
