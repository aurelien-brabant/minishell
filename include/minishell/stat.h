#ifndef STAT_H
# define STAT_H
# include "libft/gc.h"

typedef struct s_stat
{
	t_gc			global_gc;
	t_gc			tmp_gc;
	unsigned int	opt;
	char			**optargs;
	
}	t_stat;

t_stat	*getstat(void);

#endif
