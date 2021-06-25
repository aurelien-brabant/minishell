#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

void	exec(t_vector parsed);

/* REDIRECTION */

int		open_in(t_command *cmd, int *fd_in);
int		open_out(t_command *cmd, int *fd_out);

int	make_redirections(t_vector redirv, int pipefd[2], size_t index, size_t length);

/* UTILS */

void	safe_execve(char *path, char *argv[], char *envp[]);
int		close_safe(int *fd);
bool	file_exists(const char *filepath);
bool	isdir(const char *filepath);

#endif
