#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/errno.h>

#include "minishell/parser.h"

#include "libft/io.h"

void	make_redirections(int pipefd[2], int redir_fd[2], int index, int length)
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

