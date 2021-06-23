#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

void	exec(t_vector parsed);

/* REDIRECTION */

int	open_in(t_command *cmd, int *fd_in);
int	open_out(t_command *cmd, int *fd_out);

/* UTILS */

void	safe_execve(char *path, char *argv[], char *envp[]);
int		close_safe(int *fd);
bool	file_exists(const char *filepath);
void	make_redirections(int pipefd[2], int redir_fd[2],
		int index, int length);

#endif
