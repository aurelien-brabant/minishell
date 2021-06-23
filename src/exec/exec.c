#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>

#include "minishell/exec.h"
#include "minishell/env.h"
#include "minishell/error.h"
#include "minishell/stat.h"
#include "minishell/builtin.h"

#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/vector.h"
#include "libft/io.h"
#include "minishell/parser.h"

/*
static void	builtin(char *cmd, char **ag, size_t len)
{
	if (!len)
		return ;
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
*/

/*
void	exec(t_vector parsed)
{
	t_command	*argvs;
	char		*cmd;
	char		**ag;
	size_t		len;
	size_t		length;

	length = ft_vector_length(parsed);
	if (length < 1)
		return ;
	argvs = ft_vector_get(parsed, 0);
	ag = (char **)argvs->argv->args;
	cmd = ag[0];
	len = argvs->argv->length;
	builtin(cmd, ag, len);
}
*/

pid_t	*g_pids = NULL;

/*****************************************************************************/
/*                                UTILITIES                                  */
/*****************************************************************************/

/*
** Check if the current path points to a directory.
** 1 is returned if it's indeed a directory.
** 0 is returned if it's a regular file instead.
** -1 is returned if an invalid path has been passed.
*/

int	isdir(const char *path)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (read(fd, NULL, 0) == -1);
}

static int	open_in(t_command *cmd, int *fd_in)
{
	size_t			i;
	t_redirection	*redir;

	*fd_in = -1;
	i = 0;
	while (i < ft_vector_length(cmd->redir_in))
	{
		if (i > 0)
			close(*fd_in);
		redir = ft_vector_get(cmd->redir_in, i);
		*fd_in = open(redir->arg, O_RDONLY);
		if (*fd_in == -1)
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
					redir->arg, strerror(errno));
			return (1);
		}
		++i;
	}
	return (0);
}

static int	open_out(t_command *cmd, int *fd_out)
{
	size_t			i;
	t_redirection	*redir;

	*fd_out = -1;
	i = 0;
	while (i < ft_vector_length(cmd->redir_out))
	{
		if (i > 0)
			close(*fd_out);
		redir = ft_vector_get(cmd->redir_out, i);
		if (redir->type == REDIRECTION_DOUT)
			*fd_out = open(redir->arg, O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			*fd_out = open(redir->arg, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (*fd_out == -1)
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
					redir->arg, strerror(errno));
			return (1);
		}
		++i;
	}
	return (0);
}

/*
** A simple wrapper around close(2).
** Does not attempt to close a file descriptor which value is -1.
** If the address of a valid file descriptor is passed, it is closed
** and then set to -1 to indicate it has been already closed.
** The return value of close is returned.
*/

int	close_safe(int *fd)
{
	int	ret;

	ret = 0;
	if (*fd != -1)
	{
		ret = close(*fd);
		*fd = -1;
	}
	return (ret);
}

static void	safe_execve(char *path, char *argv[], char *envp[])
{
	if (execve(path, argv, envp) == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", path, strerror(errno));
		free(path);
		exit(126);
	}
}

/*****************************************************************************/
/*                               EXECUTION                                   */
/*****************************************************************************/

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
	tok = ft_strtok(path, ":");
	while (tok != NULL)
	{
		cmd_path = get_cmd_path(cmd->argv->args[0], tok);
		if (isdir(cmd_path) != -1)
			safe_execve(cmd_path, cmd->argv->args, stat_get()->env->args);
		free(cmd_path);
		tok = ft_strtok(NULL, ":");
	}
	free(path);
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv->args[0]);
}

static void	make_redirections(int pipefd[2], int redir_fd[2],
		int index, int length)
{
	if (redir_fd[1] != -1)
		dup2(redir_fd[1], STDOUT_FILENO);
	else if (index < length - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (redir_fd[0] != -1)
		dup2(redir_fd[0], STDIN_FILENO);
	else if (index > 0)
		dup2(pipefd[-2], STDIN_FILENO);
}

/*
** If a command has been provided (and not only redirections)
** execute it, using the absolute path if a valid one is provided, or
** searching for the valid path based on the value of the PATH variable.
**
** NOTE: execute_command is executed in the child process, where all required
** redirections should have been already done.
*/

static void	execute_command(t_command *cmd)
{
	char	*label;

	label = cmd->argv->args[0];
	if (isdir(label) != -1)
		safe_execve(label, cmd->argv->args, stat_get()->env->args);
	else
		execute_from_path(cmd);
}

void	process_command(t_command *cmd, int *pipefd,
		size_t index, size_t length)
{
	pid_t	pid;
	int		redir_fd[2];
	size_t	i;

	open_in(cmd, &redir_fd[0]);
	open_out(cmd, &redir_fd[1]);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		i = index;
		while (i > 0)
			close_safe(&pipefd[1 - (i-- * 2)]);
		make_redirections(pipefd, redir_fd, index, length);	
		if (cmd->argv->length > 0)
			execute_command(cmd);
		exit(0);
	}
	g_pids[index] = pid;
	close_safe(&redir_fd[0]);
	close_safe(&redir_fd[1]);
}

void	process_builtin(t_command *cmd, int *pipefd, int index, int length)
{
	int			savefd[2];	
	int			redir_fd[2];
	t_builtin	builtin;

	builtin = builtin_get(cmd->argv->args[0]);
	savefd[0] = dup(STDIN_FILENO);
	savefd[1] = dup(STDOUT_FILENO);
	open_in(cmd, &redir_fd[0]);
	open_out(cmd, &redir_fd[1]);
	pipe(pipefd);
	make_redirections(pipefd, redir_fd, index, length);	
	builtin(cmd->argv->length, cmd->argv->args);
	close(pipefd[1]);
	close_safe(&redir_fd[0]);
	close_safe(&redir_fd[1]);
	dup2(savefd[0], STDIN_FILENO);
	dup2(savefd[1], STDOUT_FILENO);
	close_safe(&savefd[0]);
	close_safe(&savefd[1]);
}

void	wait_for_pids(int *pipefd, size_t length)
{
	size_t	i;
	pid_t	pid;

	i = 0;
	while (1)
	{
		pid = wait(NULL);
		if (pid <= 0)
			break ;
		i = 0;
		while (i < length && g_pids[i] != pid)
			++i;
		close_safe(&(pipefd + (i * 2))[1]);
		if (i > 0)
			close_safe(&(pipefd + (i * 2))[-2]);
		g_pids[i] = 0;
	}
}

void	exec(t_vector parsed)
{
	t_command	*cmd;
	int			*pipefd;
	size_t		i;
	size_t		length;

	length = ft_vector_length(parsed);
	if (length == 0)
		return ;
	g_pids = assert_ptr(ft_calloc(sizeof (*g_pids), length));
	pipefd = assert_ptr(malloc(sizeof (int) * (length * 2)));
	i = 0;
	while (i < length)
	{
		cmd = ft_vector_get(parsed, i);
		if (cmd->argv->length > 0 && builtin_get(cmd->argv->args[0]))
			process_builtin(cmd, pipefd + (i * 2), i, length);
		else
			process_command(cmd, pipefd + (i * 2), i, length);
		++i;
	}
	wait_for_pids(pipefd, length);
	close_safe(pipefd + ((length - 1) * 2));
	free(g_pids);
	free(pipefd);
}
