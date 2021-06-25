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

void	process_command(t_command *cmd, int *pipefd,
		size_t index, size_t length)
{
	pid_t	pid;

	pid = 0;
	if (!pipe(pipefd))
	{
		pid = fork();
		if (pid == 0)
		{
			if (make_redirections(cmd->redir, pipefd, index, length) != 0)
				exit(2);
			if (cmd->argv->length > 0)
				execute_command(cmd);
			exit(0);
		}
	}
	g_pids[index] = pid;
}

void	close_pipes(int *pipefd, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		close_safe(&(pipefd + (i * 2))[0]);
		close_safe(&(pipefd + (i * 2))[1]);
		++i;
	}
}

void	process_builtin(t_command *cmd, int *pipefd, int index, int length)
{
	int			savefd[2];	
	t_builtin	builtin;

	builtin = builtin_get(cmd->argv->args[0]);
	savefd[0] = dup(STDIN_FILENO);
	savefd[1] = dup(STDOUT_FILENO);
	if (!pipe(pipefd))
	{
		make_redirections(cmd->redir, pipefd, index, length);	
		stat_get()->last_status_code = (unsigned char)
			builtin(cmd->argv->length, cmd->argv->args);
	}
	else
		stat_get()->last_status_code = 1;
	dup2(savefd[0], STDIN_FILENO);
	dup2(savefd[1], STDOUT_FILENO);
	close_safe(&savefd[0]);
	close_safe(&savefd[1]);
}

void	wait_for_pids(int *pipefd, size_t length)
{
	size_t	i;
	pid_t	pid;
	int		status;

	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		close_pipes(pipefd, length);
		i = 0;
		while (g_pids[i] != pid)
			++i;
		if (i == length - 1)
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
	g_pids = NULL;
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

static void	exec_loop(t_vector parsed, int *pipefd, bool *builtin_executed)
{
	t_command	*cmd;
	size_t		i;
	size_t		length;

	i = 0;
	length = ft_vector_length(parsed);
	while (i < length)
	{
		cmd = ft_vector_get(parsed, i);
		if (cmd->argv->length > 0 && builtin_get(cmd->argv->args[0]))
		{
			process_builtin(cmd, pipefd + (i * 2), i, length);
			*builtin_executed = true;
		}
		else
			process_command(cmd, pipefd + (i * 2), i, length);
		++i;
	}
}

void	exec(t_vector parsed)
{
	int			*pipefd;
	size_t		length;
	bool		builtin_executed;
	
	builtin_executed = false; 
	length = ft_vector_length(parsed);
	if (length == 0)
		return ;
	g_pids = gc_add_tmp(ft_calloc(sizeof (*g_pids), length + 1), &free);
	g_pids[length] = -1;
	pipefd = gc_add_tmp(malloc(sizeof (int) * (length * 2)), &free);
	exec_loop(parsed, pipefd, &builtin_executed);
	if (builtin_executed)
		close_pipes(pipefd, length);
	wait_for_pids(pipefd, length);
}
