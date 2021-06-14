#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

void	exec(t_vector parsed, char ***env);
char	**get_env(char **envp);
char	*get_env_value(const char *var, char **env);
void	fn_echo(char **ag, size_t len);
void	fn_cd(char **ag, char ***env, size_t len);
void	fn_pwd(void);
char	*get_pwd(void);
void	fn_export(char **ag, char ***env, size_t len);
void	fn_unset(char **ag, char ***env, size_t len);
void	fn_exit(void);
void	fn_exec(char *cmd, char **ag, char ***env);

/* UTILS */
void	free_tab(char **tab);
void	print_tab(char **tab);
int		tab_len(char **tab);

#endif
