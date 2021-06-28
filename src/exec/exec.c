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
#include "minishell/signal.h"
#include "minishell/parser.h"

#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/vector.h"
#include "libft/io.h"

pid_t	*g_pids = NULL;

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
	ttyfd[0] = dup(STDIN_FILENO);
	ttyfd[1] = dup(STDOUT_FILENO);
	pipe(pipefd);
	redir_ret = make_redirections(cmd, pipefd, ttyfd, length);
	if (length > 1)
		minishell_fork_builtin(cmd, pipefd, ttyfd, redir_ret);
	else
		stat_get()->last_status_code = builtin(cmd->sv->len,
				cmd->sv->data, false);
	dup2(ttyfd[0], STDIN_FILENO);
	dup2(ttyfd[1], STDOUT_FILENO);
	close_safe(&ttyfd[0]);
	close_safe(&ttyfd[1]);
}

void	wait_for_pids(int *pipefd, size_t length)
{
	pid_t	pid;
	int		status;
	size_t	i;

	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		close_pipes(pipefd, length);
		i = 0;
		while (g_pids[i] != pid)
			++i;
		if (pid == g_pids[i])
		{
			if (WIFSIGNALED(status))
			{
				print_sig_msg(WTERMSIG(status));
				stat_get()->last_status_code = 128 + WTERMSIG(status);
			}
			else
				stat_get()->last_status_code = WEXITSTATUS(status);
		}
		g_pids[i] = 0;
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
	g_pids = gc_add_tmp(ft_calloc(sizeof (*g_pids), pipeline->len + 1), &free);
	g_pids[pipeline->len] = -1;
	pipefd = gc_add_tmp(malloc(sizeof (int) * (pipeline->len * 2)), &free);
	exec_loop(pipeline, pipefd);
	signal(SIGINT, sig_send_to_all_children);
	signal(SIGQUIT, sig_send_to_all_children);
	wait_for_pids(pipefd, pipeline->len);
}
