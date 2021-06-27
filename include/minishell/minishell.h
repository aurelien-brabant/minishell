#ifndef MINISHELL_H
# define MINISHELL_H
# define HERE_DOC_FILEPATH "./.here_doc.txt"
# include <sys/types.h>

# include "minishell/lexer.h"
# include "minishell/exec.h"

# include "libft/string.h"

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
char	*prompt_present(void);

int		minishell_invoke(unsigned int opt, char **optargs, char **envp);
void	minishell_exit(int exit_status);

#endif
