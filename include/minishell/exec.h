#ifndef EXEC_H
# define EXEC_H

void	exec(char *cmd, char **envp);
char	**get_env(char **envp);
void	fn_echo(char *s);
void	fn_cd(char **env);
void	fn_pwd(char **env);
void	fn_export(char **env);
void	fn_unset(char *cmd, char **env);
void	fn_exit(void);

/* UTILS */
void	free_tab(char **tab);
void	print_tab(char **tab);


#endif
