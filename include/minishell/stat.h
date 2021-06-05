#ifndef STAT_H
# define STAT_H

typedef struct s_stat
{
	unsigned int	opt;
	char			**optargs;
	
}	t_stat;

t_stat	*getstat(void);

#endif
