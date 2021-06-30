#ifndef CLA_INT_H
# define CLA_INT_H

# define MAX_BOOL 10
# define MAX_STR 10
# define MAX_INT 10
# define MAX_POS 10

typedef struct s_cla_str
{
	const char	*key;
	const char	*dflt;
	char		**ptr;
}	t_cla_str;

typedef struct s_cla_bool
{
	const char	*key;
	bool		dflt;
	bool		*ptr;
}	t_cla_bool;

typedef struct s_cla_int
{
	const char		*key;
	long long int	dflt;
	long long int	*ptr;
}	t_cla_int;

typedef struct s_cla_pos
{
	int			index;
	const char	*dflt;
	char		**ptr;
}	t_cla_pos;

typedef struct s_cla
{
	int			ac;
	char		**av;
	t_cla_pos	pos[MAX_POS + 1];
	t_cla_int	ints[MAX_INT + 1];
	t_cla_str	strs[MAX_STR + 1];
	t_cla_bool	bools[MAX_BOOL + 1];
}	t_cla;

#endif
