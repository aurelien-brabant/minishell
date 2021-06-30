#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "minishell/minishell.h"
#include "minishell/parser.h"
#include "minishell/exec.h"
#include "minishell/constants.h"
#include "minishell/signal.h"

#include "libft/io.h"
#include "libft/cstring.h"

static int	handle_here_doc(t_redir *redir, int ttyfd[2])
{
	int	save_out;
	int	fd;

	save_out = dup(STDOUT_FILENO);
	dup2(ttyfd[0], STDIN_FILENO);
	dup2(ttyfd[1], STDOUT_FILENO);
	fd = here_doc_prompt(redir->arg);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
	return (fd == -1);
}

static int	handle_in_redir(t_redir *redir, int ttyfd[2])
{
	int	tmp_fd;

	if (redir->type == REDIRECTION_DIN)
		return (handle_here_doc(redir, ttyfd));
	else if (redir->type == REDIRECTION_IN)
	{
		tmp_fd = open(redir->arg, O_RDONLY | O_CLOEXEC);
		if (tmp_fd != -1)
		{
			dup2(tmp_fd, STDIN_FILENO);
			close(tmp_fd);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", redir->arg,
				strerror(errno));
			return (1);
		}
	}
	return (0);
}

static int	handle_out_redir(t_redir *redir)
{
	int	tmp_fd;

	if (redir->type == REDIRECTION_OUT)
		tmp_fd = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		tmp_fd = open(redir->arg, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (tmp_fd != -1)
	{
		dup2(tmp_fd, STDOUT_FILENO);
		close(tmp_fd);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", redir->arg,
			strerror(errno));
		return (1);
	}
	return (0);
}

int	make_file_redirections(t_redirv *rv, int ttyfd[2])
{
	t_redir		*redir;
	size_t		i;
	int			ret;

	i = 0;
	ret = 0;
	while (ret == 0 && i < rv->len)
	{
		redir = &rv->data[i];
		if (redir->type == REDIRECTION_IN || redir->type == REDIRECTION_DIN)
			ret = handle_in_redir(redir, ttyfd);
		else if (redir->type == REDIRECTION_OUT
			|| redir->type == REDIRECTION_DOUT)
			ret = handle_out_redir(redir);
		++i;
	}
	return (ret);
}

int	make_redirections(t_command *cmd, int pipefd[2], int ttyfd[2],
		size_t length)
{
	if (cmd->id < length - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (cmd->id > 0)
		dup2(pipefd[-2], STDIN_FILENO);
	return (make_file_redirections(cmd->rv, ttyfd));
}
