#ifndef EXEC_H
# define EXEC_H
# include <stdbool.h>
# include "parser.h"

void	exec(t_pipeline *pipeline);

/* REDIRECTION */

int		open_in(t_command *cmd, int *fd_in);
int		open_out(t_command *cmd, int *fd_out);

int		make_redirections(t_command *cmd, int pipefd[2], int ttyfd[2],
			size_t length);

void	minishell_fork(t_command *cmd, int *pipefd, int ttyfd[2],
			int redir_ret);

void	minishell_fork_builtin(t_command *cmd, int *pipefd, int ttyfd[2],
			int redir_ret);

int		here_doc_prompt(char *delim);

/* UTILS */

void	safe_execve(char *path, char *argv[], char *envp[]);
int		close_safe(int *fd);
void	close_pipes(int *pipefd, size_t length);
bool	file_exists(const char *filepath);
bool	isdir(const char *filepath);

#endif
