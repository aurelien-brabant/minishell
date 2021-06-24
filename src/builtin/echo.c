#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"
#include "libft/io.h"

#include <unistd.h>

int	echo_n(int argc, char *argv[])
{
	int		i;

	if (ft_strncmp("-n", argv[1], 2))
		return (0);
	i = 2;
	while (argv[1][i])
	{
		if (argv[1][i] == 'n')
			i++;
		else
			return (0);
	}
	i = 2;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDIN_FILENO);
		if (i < argc - 1)
			ft_putchar_fd(' ', 2);
		i++;
	}
	return (1);
}

int	builtin_echo(int argc, char *argv[])
{
	int		i;

	if (!argv[1])
	{
		ft_putchar_fd('\n', 2);
		return (0);
	}
	if (echo_n(argc, argv))
		return (0);
	i = 1;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 2);
		if (i < argc - 1)
			ft_putchar_fd(' ', 2);
		i++;
	}
	ft_putchar_fd('\n', STDIN_FILENO);
	return (0);
}
