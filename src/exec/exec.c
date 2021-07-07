#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minishell/minishell.h"
#include "minishell/error.h"
#include "minishell/builtin.h"
#include "minishell/signal.h"

#include "libft/core.h"

/*
** If a command has been provided (and not only redirections) execute it.
** If the provided path already points to an existing file or folder,
** an attempt to execute it will be made. 
**
** It is important to note though, that any command name which is not prefixed
** by any forward slash ('/') (being an absolute or a relative path) will 
** ALWAYS be executed from the defined PATH. Let's say an executable which's 
** name is a.out is available in the current directory, the command "a.out"
** will report the "command not found" error while the command "./a.out" will
** properly execute it.
**
** NOTE: execute_command is executed in the child process, where all required
** redirections should have been already done.
*/

void	process_command(t_command *cmd, int *pipefd, size_t length)
{
	int		redir_ret;
	int		ttyfd[2];

	ttyfd[0] = dup(STDIN_FILENO);
	ttyfd[1] = dup(STDOUT_FILENO);
	pipe(pipefd);
	redir_ret = make_redirections(cmd, pipefd, ttyfd, length);
	minishell_fork(cmd, pipefd, ttyfd, redir_ret);
	dup2(ttyfd[0], STDIN_FILENO);
	dup2(ttyfd[1], STDOUT_FILENO);
	close(ttyfd[0]);
	close(ttyfd[1]);
}

void	process_builtin(t_command *cmd, int *pipefd, int length)
{
	t_builtin	builtin;
	int			ttyfd[2];	
	int			redir_ret;

	builtin = builtin_get(cmd->sv->data[0]);
	if (builtin == &builtin_exit)
		builtin(cmd->sv->len, cmd->sv->data, false);
	ttyfd[0] = dup(STDIN_FILENO);
	ttyfd[1] = dup(STDOUT_FILENO);
	pipe(pipefd);
	redir_ret = make_redirections(cmd, pipefd, ttyfd, length);
	if (length > 1)
		minishell_fork_builtin(cmd, pipefd, ttyfd, redir_ret);
	else if (builtin != &builtin_exit)
		g_msh.status = builtin(cmd->sv->len,
				cmd->sv->data, false);
	dup2(ttyfd[0], STDIN_FILENO);
	dup2(ttyfd[1], STDOUT_FILENO);
	close_safe(&ttyfd[0]);
	close_safe(&ttyfd[1]);
	if (length == 1)
		close_pipes(pipefd - (cmd->id * 2), cmd->id + 1);
}

void	wait_for_pids(size_t length)
{
	pid_t	pid;
	int		status;
	size_t	i;

	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		i = 0;
		while (g_msh.pids[i] != pid)
			++i;
		if (pid == g_msh.pids[length - 1])
		{
			if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
			{
				print_sig_msg(WTERMSIG(status));
				g_msh.status = 128 + WTERMSIG(status);
			}
			else
				g_msh.status = WEXITSTATUS(status);
		}
		g_msh.pids[i] = 0;
	}
}

/*
** Execute each command stored in the pipeline.
**
** A command can either be a shell builtin or an external program that lives
** outside the minishell program.
**
** The address of a boolean value is passed, which should indicate at the
** end of exec_loop whether or not a shell builtin has been executed.
** This is important to know because if it is the case, it means that
** a command in the pipeline already exited by definition,  because a shell
** builtin is not a subprocess. Therefore, all the pipes opened for the
** pipeline must be closed before even waiting for the termination of other
** commands.
*/

static void	exec_loop(t_pipeline *pipeline, int *pipefd)
{
	t_command	*cmd;
	size_t		i;

	i = 0;
	while (i < pipeline->len)
	{
		cmd = &pipeline->data[i];
		if (cmd->sv->len > 0 && builtin_get(cmd->sv->data[0]))
			process_builtin(cmd, pipefd + (i * 2), pipeline->len);
		else
			process_command(cmd, pipefd + (i * 2), pipeline->len);
		++i;
	}
}

void	exec(t_pipeline *pipeline)
{
	int			*pipefd;

	if (pipeline->len == 0)
		return ;
	g_msh.pids = gc_add_tmp(ft_calloc(sizeof (*g_msh.pids),
				pipeline->len + 1), &free);
	g_msh.pids[pipeline->len] = -1;
	pipefd = gc_add_tmp(malloc(sizeof (int) * (pipeline->len * 2)), &free);
	exec_loop(pipeline, pipefd);
	signal(SIGINT, sig_send_to_all_children);
	signal(SIGQUIT, sig_send_to_all_children);
	wait_for_pids(pipeline->len);
}
