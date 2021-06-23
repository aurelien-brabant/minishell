#include "minishell/minishell.h"
#include "minishell/env.h"
#include "libft/cstring.h"
#include "libft/ctype.h"
#include <stdlib.h>
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

int	fn_export(char **ag, size_t len)
{
	char	*var_name;
	char	*s;

	if (len == 2)
	{
		s = ft_strdup(ag[1]);
		var_name = s;
		s = ft_strchr(s, '=');
		if (s == NULL)
			s = "";
		else
			*s++ = '\0';
		if (check_var_name(var_name))
			minishell_setenv(var_name, s);
		else
			ft_dprintf(2, "minishel: export \"%s\" : identifiant non valable\n",
				var_name);
		free(var_name);
	}
	return (0);
}
