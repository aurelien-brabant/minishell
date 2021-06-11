#ifndef EXEC_H
# define EXEC_H

void	exec(char *cmd, char **envp);
char	**get_env(char **envp);
void	fn_env(char **envp);
void	fn_echo(char *s);
void	fn_exit(void);

#endif
