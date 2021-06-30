#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <stdint.h>

# include "libft/gc.h"

# include "minishell/exec.h"

typedef enum e_option_type
{
	OPTION_TYPE_VERSION = 0,
	OPTION_TYPE_DEBUG,
	OPTION_TYPE_COMMAND,
	OPTION_TYPE_HELP,
	OPTION_TYPE_MAX,
}	t_option_type;

typedef struct s_minishell_data
{
	pid_t		*pids;
	uint8_t		status;
	t_gc		*gc_tmp;
	t_gc		*gc_glob;
	t_stringv	*env;
}	t_minishell_data;

extern t_minishell_data	g_msh;

int		parse_clopt(int argc, char *argv[], unsigned int *options,
			char **optargs);
void	minishell_output_usage(void);
char	*prompt_present(void);

int		minishell_invoke(unsigned int opt, char **optargs, char **envp);
void	minishell_exit(int exit_status);

#endif
