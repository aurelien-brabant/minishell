#include <stdlib.h>

#include "minishell/minishell.h"
#include "minishell/env.h"
#include "minishell/builtin.h"

#include "libft/cstring.h"
#include "libft/ctype.h"
#include "libft/io.h"

static int	check_var_name(char *s)
{
	int		i;

	i = 0;
	if (ft_isdigit(s[0]))
		return (0);
	while (s[i])
	{
		if (ft_isdigit(s[i]) || ft_isupper(s[i]) || s[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	builtin_export(int argc, char *argv[])
{
	char	*var_name;
	char	*s;

	if (argc == 2)
	{
		s = ft_strdup(argv[1]);
		var_name = s;
		s = ft_strchr(s, '=');
		if (s == NULL)
			s = "";
		else
			*s++ = '\0';
		if (check_var_name(var_name))
			minishell_setenv(var_name, s);
		else
		{
			ft_dprintf(2, "minishell: export \"%s\": not a valid variable"
					" identifier\n", var_name);
			return (1);
		}
		free(var_name);
	}
	return (0);
}
