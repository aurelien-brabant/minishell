#ifndef ENV_H
# define ENV_H
# include <stdbool.h>

char	*minishell_getenv(char *var_name);
char	*minishell_setenv(char *var_name, char *value);
void	minishell_unsetenv(char *var_name);
void	minishell_printenv(void);
bool	is_valid_env_var_name(const char *name);
#endif
