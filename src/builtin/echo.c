#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"
#include "libft/io.h"

#include <unistd.h>

static int	skip_options(int argc, char *argv[])
{
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		if (ft_strncmp("-n", argv[i], 2))
			return (i);
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'n')
				j++;
			else
				return (i);
		}
		i++;
	}
	return (i);
}

static int	echo_n(int argc, char *argv[])
{
	int		i;

	i = skip_options(argc, argv);
	if (i < 2)
		return (0);
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	return (1);
}

int	builtin_echo(int argc, char *argv[], bool forked)
{
	int		i;

	(void)forked;
	if (!argv[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	if (echo_n(argc, argv))
		return (0);
	i = 1;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
