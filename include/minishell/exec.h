#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

typedef int (*t_builtin)(char *argv[], size_t argc);

void	exec(t_vector parsed);
char	*get_pwd(void);

/* BUILTINS */

int		fn_echo(char **ag, size_t len);
int		fn_cd(char **ag, size_t argc);
int		fn_pwd(char *argv[], size_t argc);
int		fn_export(char **ag, size_t len);
int		fn_unset(char **ag, size_t len);
int		fn_exit(char *argv[], size_t argc);

void	fn_exec(char *cmd, char **ag);

/* UTILS */
void	free_tab(char **tab);
void	print_tab(char **tab);
int		tab_len(char **tab);

#endif
