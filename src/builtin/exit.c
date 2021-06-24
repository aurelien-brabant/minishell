#include <unistd.h>

#include "minishell/minishell.h"
#include "minishell/builtin.h"

#include "libft/io.h"
#include "libft/strconv.h"
#include "libft/ctype.h"

int	check_digit(char *s)
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

int	builtin_exit(int argc, char *argv[])
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc == 2)
	{
		if (!check_digit(argv[1]))
			minishell_exit(ft_atoi(argv[1]) % 256);
		else if (check_digit(argv[1]) > 0)
			minishell_exit((256 + ft_atoi(argv[1]) % 256));
		else
		{
			ft_dprintf(STDERR_FILENO, "minishell: exit: %s : "
				"argument numérique nécessaire\n", argv[1]);
			minishell_exit(2);
			return (2);
		}
	}
	else if (argc > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: trop d'arguments\n");
		return (1);
	}
	minishell_exit(0);
	return (0);
}
