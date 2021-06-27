#ifndef STAT_H
# define STAT_H
# include <stdbool.h>
# include "libft/gc.h"

# include "minishell/argv.h"

typedef struct s_stat
{
	t_gc			global_gc;
	t_gc			tmp_gc;
	unsigned int	opt;
	char			**optargs;
	bool			error;
	unsigned char	last_status_code;
	t_argv			*env;
}	t_stat;

t_stat	*stat_get(void);
void	stat_init(unsigned int opt, char **optargs, char **envp);
void	stat_destroy(void);

#endif
