#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

#include "libft/cstring.h"
#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/constants.h"

static const struct s_options
{
	char			*long_opt;
	char			short_opt;
	unsigned int	flag;
	t_option_type	type;
	bool			requires_arg;
	char			*usage;
} g_options[] = {
	{
		.long_opt = "version",
		.short_opt = 'v',
		.type = OPTION_TYPE_VERSION,
		.flag = 1 << OPTION_TYPE_VERSION,
		.requires_arg = false,
		.usage = "get the version of minishell"
	},
	{
		.long_opt = "debug",
		.short_opt = 'd',
		.type = OPTION_TYPE_DEBUG,
		.flag = 1 << OPTION_TYPE_DEBUG,
		.requires_arg = false,
		.usage = "enable debug mode (what does it do ? You'll see by yourself!)"
	},
	{
		.long_opt = "command",
		.short_opt = 'c',
		.type = OPTION_TYPE_COMMAND,
		.flag = 1 << OPTION_TYPE_COMMAND,
		.requires_arg = true,
		.usage = "<command> Run a single command in a non-interactive mode"
	},
	{
		.long_opt = "help",
		.short_opt = 'h',
		.type = OPTION_TYPE_HELP,
		.flag = 1 << OPTION_TYPE_HELP,
		.requires_arg = false,
		.usage = "Output this awesome help message"
	}
};

/*
** Returns the index in g_options where the corresponding option can be
** retrieved. -1 is returned if option could not be found.
**
** option_kind: 0 for short, 1 for long
*/

static int	get_option_index(const char *arg, int opt_kind)
{
	int	i;

	i = 0;
	while (i < OPTION_TYPE_MAX)
	{
		if ((opt_kind == 0 && *arg == g_options[i].short_opt)
			|| (opt_kind == 1 && ft_strcmp(g_options[i].long_opt, arg) == 0))
			return (i);
		++i;
	}
	return (-1);
}

static int	parse_long_options(int argc, char *argv[], unsigned int *options,
				char **optargs)
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
			ft_dprintf(STDERR_FILENO, "minishell: \"%s\" unknown\n", argv[i]);
			return (1);
		}
		*options |= g_options[opti].flag;
		if (g_options[opti].requires_arg && ++i < argc)
			optargs[g_options[opti].type] = argv[i];
	}
	return (0);
}

static int	parse_short_options(int argc, char *argv[], unsigned int *options,
				char **optargs)
{
	int		i;
	int		opti;
	char	*arg;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-' || argv[i][1] == '-')
			continue ;
		arg = &argv[i][1];
		while (*arg != '\0')
		{
			opti = get_option_index(arg, 0);
			if (opti == -1)
			{
				ft_dprintf(STDERR_FILENO, "minishell: \"-%c\" unknown\n", *arg);
				return (1);
			}
			*options |= g_options[opti].flag;
			if (g_options[opti].requires_arg && ++i < argc)
				optargs[g_options[opti].type] = argv[i];
			++arg;
		}
	}
	return (0);
}

/*
** Output the complete usage of minishell, describing all the available
** options.
*/

void	minishell_output_usage(void)
{
	int	i;

	i = 0;
	ft_printf("Usage: %s\n", MINISHELL_USAGE);
	ft_printf("Available options are:\n");
	while (i < OPTION_TYPE_MAX)
	{
		ft_printf("-%c | --%s\t\t%s\n", g_options[i].short_opt,
			g_options[i].long_opt, g_options[i].usage);
		++i;
	}
}

/*
** Parse Command Line Options
** This function is called to parse command line options ONLY, not positional
** parameters (which are not accepted by minishell anyway). Short format
** (e.g: "-d") as well as long format (e.g: "--debug") are accepted.
**
** - ARGUMENTS -
** Up to one argument can be provided for each option; it is assumed to be
** the next argument directly following the option. These arguments are stored
** in the optargs string array. The argument corresponding to a given
** option can therefore be accessed by directly subscripting the array, like
** so: optargs[OPTION_TYPE_COMMAND].
**
** The parse_clopt function ensures that options that need an argument got
** one. If that's not the case, an error will be thrown.
*/

int	parse_clopt(int argc, char *argv[], unsigned int *options, char **optargs)
{
	size_t	i;

	*options = 0;
	if (parse_long_options(argc, argv, options, optargs) != 0
		|| parse_short_options(argc, argv, options, optargs) != 0)
		return (1);
	i = 0;
	while (i < OPTION_TYPE_MAX)
	{
		if (g_options[i].flag & *options && g_options[i].requires_arg
			 && optargs[i] == NULL)
		{
			ft_dprintf(STDERR_FILENO, "minishell: \"--%s\" option requires an"
				" argument\n", g_options[i].long_opt);
			return (1);
		}
		++i;
	}
	return (0);
}
