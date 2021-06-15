#include "minishell/exec.h"
#include "minishell/env.h"
//#include "minishell/stat.h"
#include "libft/cstring.h"
//#include "libft/io.h"
#include "libft/vector.h"
//#include <signal.h>
//#include <sys/wait.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>

static void	builtin(char *cmd, char **ag, size_t len)
{
	if (!ft_strcmp(cmd, "echo"))
		fn_echo(ag, len);
	else if (!ft_strcmp(cmd, "cd"))
		fn_cd(ag);
	else if (!ft_strcmp(cmd, "pwd"))
		fn_pwd();
	else if (!ft_strcmp(cmd, "export"))
		fn_export(ag, len);
	else if (!ft_strcmp(cmd, "unset"))
		fn_unset(ag, len);
	else if (!ft_strcmp(cmd, "env"))
		minishell_printenv();
	else if (!ft_strcmp(cmd, "exit"))
		fn_exit();
	else
		fn_exec(cmd, ag);
}

void	exec(t_vector parsed)
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
		builtin(cmd, ag, len);
//		i++;
//	}
}
