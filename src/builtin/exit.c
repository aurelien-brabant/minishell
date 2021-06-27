#include <unistd.h>

#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/io.h"
#include "libft/strconv.h"
#include "libft/ctype.h"

static int	check_digit(char *s)
{
	int		i;
	int		neg;

	i = 0;
	neg = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			neg++;
		i++;
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	return (neg);
}

static int	check_args(char *argv)
{
	if (check_digit(argv) == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s : "
			"numeric argument required\n", argv);
		minishell_exit(2);
		return (2);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
}

int	builtin_exit(int argc, char *argv[], bool forked)
{
	if (forked)
		return (0);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc == 2)
	{
		if (!check_digit(argv[1]))
			minishell_exit(ft_atoi(argv[1]) % 256);
		else if (check_digit(argv[1]) > 0)
			minishell_exit((256 + ft_atoi(argv[1]) % 256));
	}
	else if (argc >= 2)
		return (check_args(argv[1]));
	minishell_exit(0);
	return (0);
}
