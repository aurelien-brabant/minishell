#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

void	exec(t_vector parsed);
void	fn_echo(char **ag, size_t len);
void	fn_cd(char **ag);
void	fn_pwd(void);
char	*get_pwd(void);
void	fn_export(char **ag, size_t len);
void	fn_unset(char **ag, size_t len);
void	fn_exit(void);
void	fn_exec(char *cmd, char **ag);

/* UTILS */
void	free_tab(char **tab);
void	print_tab(char **tab);
int		tab_len(char **tab);

#endif
