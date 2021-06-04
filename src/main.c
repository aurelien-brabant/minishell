#include <unistd.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/constants.h"

int	main(int argc, char *argv[])
{
	unsigned int	options;

	if (parsecl(argc, argv, &options) != 0)
		minishell_output_usage();
}
