#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "minishell/parser.h"
#include "minishell/exec.h"
#include "minishell/constants.h"

#include "libft/io.h"
#include "libft/cstring.h"

static int	handle_in_redir(t_redirection *redir)
{
	int	tmp_fd;

	tmp_fd = open(redir->arg, O_RDONLY | O_CLOEXEC);
	if (tmp_fd != -1)
		dup2(tmp_fd, STDIN_FILENO);
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", redir->arg,
			strerror(errno));
		return (1);
	}
	return (0);
}

static int	handle_out_redir(t_redirection *redir)
{
	int	tmp_fd;

	if (redir->type == REDIRECTION_OUT)
		tmp_fd = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
	else
		tmp_fd = open(redir->arg, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	if (tmp_fd != -1)
		dup2(tmp_fd, STDOUT_FILENO);
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", redir->arg,
			strerror(errno));
		return (1);
	}
	return (0);
}

int	make_file_redirections(t_vector redirv)
{
	size_t			i;
	size_t			length;
	t_redirection	*redir;
	int				ret;

	i = 0;
	ret = 0;
	length = ft_vector_length(redirv);
	while (ret == 0 && i < length)
	{
		redir = ft_vector_get(redirv, i);
		if (redir->type == REDIRECTION_IN)
			ret = handle_in_redir(redir);
		else if (redir->type == REDIRECTION_OUT
				|| redir->type == REDIRECTION_DOUT)
			ret = handle_out_redir(redir);
		++i;
	}
	return (ret);
}

int	make_redirections(t_vector redirv, int pipefd[2], size_t index, size_t length)
{
	size_t	i;

	if (index < length - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (index > 0)
		dup2(pipefd[-2],  STDIN_FILENO);
	pipefd = pipefd - (index * 2);
	i = 0;
	while (i <= index)
	{
		ft_dprintf(2, "Close %d\n", (pipefd + (i * 2))[0]);
		ft_dprintf(2, "Close %d\n", (pipefd + (i * 2))[1]);
		close_safe(pipefd + (i * 2));
		close_safe(pipefd + (i * 2) + 1);
		i++;
	}
	return (make_file_redirections(redirv));
}

/*
int	open_in(t_command *cmd, int *fd_in)
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

int	open_out(t_command *cmd, int *fd_out)
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
*/
