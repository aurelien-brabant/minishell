#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#include "minishell/parser.h"
#include "minishell/builtin.h"
#include "minishell/exec.h"
#include "minishell/signal.h"
#include "minishell/env.h"
#include "minishell/stat.h"

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
	{
		ft_dprintf(STDERR_FILENO, "PATH variable is not set!\n");
		exit(127);
	}
	path = ft_strdup(path);
	if (cmd->argv->args[0][0] != '\0')
	{
		tok = ft_strtok(path, ":");
		while (tok != NULL)
		{
			cmd_path = get_cmd_path(cmd->argv->args[0], tok);
			if (file_exists(cmd_path))
				safe_execve(cmd_path, cmd->argv->args, stat_get()->env->args);
			free(cmd_path);
			tok = ft_strtok(NULL, ":");
		}
	}
	free(path);
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv->args[0]);
	exit(127);
}

static void	execute_command(t_command *cmd)
{
	char	*label;
	size_t	i;

	label = cmd->argv->args[0];
	if (file_exists(label))
	{
		i = 0;
		while (label[i] == '.')
			++i;
		if (i <= 2 && label[i] == '/')
			safe_execve(label, cmd->argv->args, stat_get()->env->args);
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
		signal(SIGSTOP, SIG_DFL);
		close(ttyfd[0]);
		close(ttyfd[1]);
		close_pipes(pipefd - (cmd->id * 2), cmd->id + 1);
		if (redir_ret != 0)
			exit(2);
		if (cmd->argv->length > 0)
			execute_command(cmd);
		exit(0);
	}
	g_pids[cmd->id] = pid;
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
			exit(2);
		builtin = builtin_get(cmd->argv->args[0]);
		exit(builtin(cmd->argv->length, cmd->argv->args, true));
	}
	g_pids[cmd->id] = pid;
}
