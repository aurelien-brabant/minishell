#include "minishell/exec.h"
#include "minishell/env.h"
#include "minishell/signal.h"
#include "libft/cstring.h"
#include "libft/vector.h"
#include "libft/io.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	builtin(char **cmd, size_t len)
{
	int		ret;

	if (!len)
		exit(errno) ;
	if (!ft_strcmp(cmd[0], "echo"))
		fn_echo(cmd, len);
	else if (!ft_strcmp(cmd[0], "cd"))
		fn_cd(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		fn_pwd();
	else if (!ft_strcmp(cmd[0], "export"))
		fn_export(cmd, len);
	else if (!ft_strcmp(cmd[0], "unset"))
		fn_unset(cmd, len);
	else if (!ft_strcmp(cmd[0], "env"))
		minishell_printenv();
	else if (!ft_strcmp(cmd[0], "exit"))
		fn_exit();
	else
	{
		g_pid[PID_CHILD] = fork();
		if (!g_pid[PID_CHILD])
			fn_exec(cmd);
		waitpid(g_pid[PID_CHILD], &ret, 0);
		g_pid[PID_CHILD] = 0;
	}
}

static void	exec_cmd(int *fd, int *pipefd, size_t i, t_command *cmd)
{
	size_t	len;

	len = cmd->argv->length;
	if (i == 0)
		dup2(fd[0], STDIN_FILENO);
	else
		dup2(pipefd[-2], STDIN_FILENO);
	if (i == len - 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(pipefd[1], STDOUT_FILENO);
	builtin(cmd->argv->args, len);
}

static void	close_fd(size_t i, size_t len, int *fd)
{
	if (!i && fd[0] != -1)
	{
		if (close(fd[0]))
			ft_putstr_fd("fd close error!\n", 2);
	}
	if (i == len && fd[1] != -1)
	{
		if (close(fd[1]))
			ft_putstr_fd("fd close error!\n", 2);
	}
}

static void	close_pipe(size_t i, int *current_pipefd)
{
	if (i && current_pipefd[-2] != -1)
	{
		close(current_pipefd[-2]);
		current_pipefd[-2] = -1;
	}
	close(current_pipefd[1]);
}

static void	exec_pipe(size_t i, t_vector parsed, int *pipefd)
{
	t_command	*cmd;
	t_redirection	*redir_in;
	t_redirection	*redir_out;
	int			fd[2];
	int			*current_pipefd;

	cmd  = ft_vector_get(parsed, i);
	redir_in = cmd->redir_in;
	if (redir_in && redir_in->type == REDIRECTION_IN)
	{
		fd[0] = open(redir_in->arg, O_RDONLY);
		if (fd[0] <= 0)
			ft_dprintf(STDERR_FILENO, "%s: %s\n", strerror(errno), redir_in->arg);
	}
	redir_out = ft_vector_get(cmd->redir_out, i);
	if (redir_out && redir_out->type == REDIRECTION_OUT)
	{
		fd[1] = open(redir_out->arg, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd[1] <= 0)
			ft_dprintf(STDERR_FILENO, "%s: %s\n", strerror(errno), redir_out->arg);
	}
	current_pipefd = pipefd + (i * 2);
	pipe(current_pipefd);
	exec_cmd(fd, current_pipefd, i, cmd);
	close_pipe(i, current_pipefd);
	close_fd(i, ft_vector_length(parsed), fd);
}

/*
static void	run_unique_cmd(t_vector parsed)
{
	t_command	*argvs;
	char		*cmd;
	char		**ag;
	size_t		len;
	
	argvs = ft_vector_get(parsed, 0);
	ag = (char **)argvs->argv->args;
	cmd = ag[0];
	len = argvs->argv->length;
	builtin(cmd, ag, len);
}
*/

void	exec(t_vector parsed)
{
	size_t	length;
	size_t	i;
	int		*pipefd;

	length = ft_vector_length(parsed);
	if (length < 1)
		return ;
	else if (length >= 1)
	{
		pipefd = (int *)malloc(sizeof(int) * (length * 2));
		if (!pipefd)
			return ;
		i = 0;
		while (i < length)
		{
			exec_pipe(i, parsed, pipefd);
			i++;
		}
	}
/*	else
		run_unique_cmd(parsed);*/
//	while (wait(NULL) > 0)
//		;
}
