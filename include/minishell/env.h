#ifndef ENV_H
# define ENV_H
char	*minishell_getenv(char *var_name);
char	*minishell_setenv(char *var_name, char *value);
void	minishell_unsetenv(char *var_name);
void	minishell_printenv(void);
#endif
