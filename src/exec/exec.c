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
	return (fd != -1 && read(fd, NULL, 0) == -1 && close(fd) == 0);
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

void	execute_command(t_command *cmd, int *pipefd,
		size_t index, size_t length)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	size_t	i;

	if (open_in(cmd, &fd_in) || open_out(cmd, &fd_out) || pipe(pipefd))
		return ;
	pid = fork();
	if (pid == 0)
	{
		i = index;
		while (i > 0)
			close_safe(&pipefd[1 - (i-- * 2)]);
		if (index < length - 1)
			dup2(pipefd[1], STDOUT_FILENO);
		else if (fd_out != -1)
			dup2(fd_out, STDOUT_FILENO);
		if (fd_in != -1)
			dup2(fd_in, STDIN_FILENO);
		else if (index > 0)
			dup2(pipefd[-2], STDIN_FILENO);
		execve(cmd->argv->args[0], cmd->argv->args, stat_get()->env->args);
	}
	g_pids[index] = pid;
	close_safe(&fd_in);
	close_safe(&fd_out);
}

void	wait_for_pids(int *pipefd, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		waitpid(g_pids[i], NULL, 0);
		close_safe(&(pipefd + (i * 2))[1]);
		if (i > 0)
			close_safe(&(pipefd + (i * 2))[-2]);
		++i;
	}
}

void	exec(t_vector parsed)
{
	t_command	*cmd;
	int			*pipefd;
	size_t		i;
	size_t		length;
	int			isdir_ret;

	length = ft_vector_length(parsed);
	if (length == 0)
		return ;
	g_pids = assert_ptr(ft_calloc(sizeof (*g_pids), length));
	pipefd = assert_ptr(malloc(sizeof (int) * (length * 2)));
	i = 0;
	while (i < length)
		pipe(pipefd + (i++ * 2));
	i = 0;
	while (i < length)
	{
		cmd = ft_vector_get(parsed, i);
		if (cmd->argv->length == 0)
		{
			++i;
			continue ;
		}
		isdir_ret = isdir(cmd->argv->args[0]);
		if (isdir_ret)
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
					cmd->argv->args[0], strerror(EISDIR));
		}
		else if (isdir_ret == 0)
			execute_command(cmd, pipefd + (i * 2), i, length);
		++i;
	}
	wait_for_pids(pipefd, length);
}
