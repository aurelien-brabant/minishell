#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#include "minishell/parser.h"
#include "minishell/builtin.h"
#include "minishell/exec.h"
#include "minishell/signal.h"
#include "minishell/env.h"
#include "minishell/minishell.h"
#include "minishell/error.h"

#include "libft/cstring.h"
#include "libft/io.h"

static char	*get_cmd_path(const char *cmd, const char *path)
{
	char	*cmd_path;
	size_t	i;

	cmd_path = malloc(sizeof (*cmd_path) + ft_strlen(cmd)
			+ ft_strlen(path) + 2);
	if (cmd_path == NULL)
		return (NULL);
	i = 0;
	while (*path != '\0')
		cmd_path[i++] = *path++;
	cmd_path[i++] = '/';
	while (*cmd != '\0')
		cmd_path[i++] = *cmd++;
	cmd_path[i] = '\0';
	return (cmd_path);
}

static void	execute_from_path(t_command *cmd)
{
	char	*path;
	char	*tok;
	char	*cmd_path;

	path = minishell_getenv("PATH");
	if (path == NULL)
		ft_dprintf(STDERR_FILENO, "PATH variable is not set!\n");
	else
		path = gc_add_tmp(ft_strdup(path), &free);
	if (path && cmd->sv->data[0][0] != '\0' && cmd->sv->data[0][0] != '.')
	{
		tok = ft_strtok(path, ":");
		while (tok != NULL)
		{
			cmd_path = gc_add_tmp(get_cmd_path(cmd->sv->data[0], tok), &free);
			if (file_exists(cmd_path))
				safe_execve(cmd_path, cmd->sv->data, g_msh.env->data);
			tok = ft_strtok(NULL, ":");
		}
	}
	ft_dprintf(2, "minishell: %s: command not found\n", cmd->sv->data[0]);
	minishell_exit(127);
}

static void	execute_command(t_command *cmd)
{
	size_t	i;
	char	*label;

	label = cmd->sv->data[0];
	if (file_exists(label))
	{
		i = 0;
		while (label[i] == '.')
			++i;
		if (i <= 2 && label[i] == '/')
			safe_execve(label, cmd->sv->data, g_msh.env->data);
	}
	execute_from_path(cmd);
}

void	minishell_fork(t_command *cmd, int *pipefd, int ttyfd[2], int redir_ret)
{
	int		pid;
	size_t	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(ttyfd[0]);
		close(ttyfd[1]);
		close_pipes(pipefd - (cmd->id * 2), cmd->id + 1);
		if (redir_ret != 0)
			minishell_exit(2);
		if (cmd->sv->len > 0)
			execute_command(cmd);
		minishell_exit(0);
	}
	g_msh.pids[cmd->id] = pid;
}

void	minishell_fork_builtin(t_command *cmd, int *pipefd, int ttyfd[2],
		int redir_ret)
{
	t_builtin	builtin;
	int			pid;
	size_t		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGSTOP, SIG_DFL);
		close(ttyfd[0]);
		close(ttyfd[1]);
		close_pipes(pipefd - (cmd->id * 2), cmd->id + 1);
		if (redir_ret != 0)
			minishell_exit(2);
		builtin = builtin_get(cmd->sv->data[0]);
		minishell_exit(builtin(cmd->sv->len, cmd->sv->data, true));
	}
	g_msh.pids[cmd->id] = pid;
}
