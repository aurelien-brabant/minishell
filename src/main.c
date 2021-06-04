#include <unistd.h>

#include "libft/io.h"
#include "libft/cstring.h"

#include "minishell/minishell.h"
#include "minishell/constants.h"

int	main(int argc, char *argv[])
{
	unsigned int	options;
	char			*optargs[OPTION_TYPE_MAX];

	ft_memset(optargs, 0, sizeof (char *) * OPTION_TYPE_MAX);
	if (parsecl(argc, argv, &options, optargs) != 0)
	{
		minishell_output_usage();
		return (1);
	}
	if (options & (1 << OPTION_TYPE_VERSION))
	{
		ft_printf("minishell v%s by %s\n", MINISHELL_VERSION, MINISHELL_AUTHOR);
		return (0);
	}
	ft_printf("option -c: %s\n", optargs[OPTION_TYPE_COMMAND]);
}
