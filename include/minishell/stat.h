#ifndef STAT_H
# define STAT_H
# include <stdbool.h>
# include "libft/gc.h"

# include "minishell/datastructure.h"

typedef struct s_stat
{
	t_gc			global_gc;
	t_gc			tmp_gc;
	unsigned int	opt;
	char			**optargs;
	t_stringv		*env;
}	t_stat;

t_stat	*stat_get(void);
void	stat_init(unsigned int opt, char **optargs, char **envp);
void	stat_destroy(void);

#endif
