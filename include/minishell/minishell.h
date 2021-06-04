#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_option_type
{
	OPTION_TYPE_VERSION = 0,
	OPTION_TYPE_DEBUG,
	OPTION_TYPE_COMMAND,
	OPTION_TYPE_HELP,
	OPTION_TYPE_MAX,
}	t_option_type;

int		parse_clopt(int argc, char *argv[], unsigned int *options,
			char **optargs);
void	minishell_output_usage(void);

#endif
