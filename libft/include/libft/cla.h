#ifndef CLA_H	
# define CLA_H
# include "libft/types.h"

typedef enum e_cla_msg
{
	CLA_MSG_TOO_MUCH_POS = 0,
	CLA_MSG_TOO_FEW_POS,
	CLA_MSG_FORBIDDEN_TOKEN,
	CLA_MSG_TOTAL,
}	t_cla_msg;

typedef struct s_cla_config
{
	char	*msg[CLA_MSG_TOTAL];
	int		min_pos;
	int		max_pos;
	char	**allowed_opt;
	char	**allowed_pos;
}	t_cla_config;

void			*ft_cla_init(int ac, char **av);
void			ft_cla_parse(void *cla);
char			*ft_cla_str_var(void *cla, char **var, const char *key,
					const char *dflt);
bool			ft_cla_bool_var(void *cla, bool *var, const char *key,
					bool dflt);
long long int	ft_cla_int_var(void *cla, long long int *var,
					const char *key, long long int dflt);
char			*ft_cla_pos_var(void *cla, char **var, int index,
					const char *dflt);
bool			ft_cla_sanity_check(void *cla, t_cla_config *conf, char *err);
t_cla_config	ft_cla_get_config(void);

#endif
