#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/parsecl.h"
#include "minishell/constants.h"

static const t_option	g_options[] = {
	{
		.long_opt = "version",
		.short_opt = 'v',
		.flag = OPTION_VERSION,
	},
	{
		.long_opt = "debug",
		.short_opt = 'd',
		.flag = OPTION_DEBUG,
	}
};

void	minishell_output_usage(void)
{
	int	i;
	int	opt_nb;

	i = 0;
	opt_nb = sizeof (g_options) / sizeof (t_option);
	ft_printf("Usage: %s\n", MINISHELL_USAGE);
	ft_printf("Available options are:\n");
	while (i < opt_nb)
	{
		ft_printf("-%c | --%s\t\t%s\n", g_options[i].short_opt,
			g_options[i].long_opt, "usage");
		++i;
	}
}

/*
** option_kind: 0 for short, 1 for long
*/

static int	get_option_index(const char *arg, int opt_kind)
{
	int	i;
	int	opt_nb;

	opt_nb = sizeof (g_options) / sizeof (t_option);
	i = 0;
	while (i < opt_nb)
	{
		if ((opt_kind == 0 && *arg == g_options[i].short_opt)
			|| (opt_kind == 1 && ft_strcmp(g_options[i].long_opt, arg) == 0))
			return (i);
		++i;
	}
	return (-1);
}

/*
** Parse long options, i.e arguments that start with the "--" prefix.
** If any argument prefixed by "--" is not in the list of available options,
** an error message is outputed on STDERR and 1 is returned as an error
** code.
*/

static int	parse_long_options(int argc, char *argv[],
					unsigned int *options)
{
	int			i;
	int			opti;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strhsprfx(argv[i], "--"))
			continue ;
		opti = get_option_index(&argv[i][2], 1);
		if (opti == -1)
		{
			ft_dprintf(STDERR_FILENO, "Unknown short opt: \"%s\"\n", argv[i]);
			return (1);
		}
		*options |= g_options[opti].flag;
	}
	return (0);
}

static int	parse_short_options(int argc, char *argv[], unsigned int *options)
{
	int		i;
	int		opti;
	char	*arg;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			continue ;
		arg = &argv[i][1];
		while (*arg != '\0')
		{
			opti = get_option_index(arg, 0);
			if (opti == -1)
			{
				ft_dprintf(STDERR_FILENO, "Unknown short opt: \"-%c\"\n", *arg);
				return (1);
			}
			*options |= g_options[opti].flag;
			++arg;
		}
	}
	return (0);
}

int	parsecl(int argc, char *argv[], unsigned int *options)
{
	*options = 0;
	if (parse_long_options(argc, argv, options) != 0
		|| parse_short_options(argc, argv, options) != 0)
		return (1);
	return (0);
}
