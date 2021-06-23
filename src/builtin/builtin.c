#include "libft/cstring.h"

#include "minishell/exec.h"
#include "minishell/builtin.h"

static const struct s_builtin_entry
{
	const char	*id;
	t_builtin	builtin;
}	g_builtin_tab[] = {
	{
		.id = "exit",
		.builtin = builtin_exit,
	},
	{
		.id = "cd",
		.builtin = builtin_cd,
	},
	{
		.id = "export",
		.builtin = builtin_export,
	},
	{
		.id = "unset",
		.builtin = builtin_unset
	},
	{
		.id = "echo",
		.builtin = builtin_echo,
	},
	{
		.id = "pwd",
		.builtin = builtin_pwd,
	},
	{
		.id = "env",
		.builtin = builtin_env,
	},
	{
		.id = NULL,
		.builtin = NULL,
	},
};

/*
** Retrieve the specified builtin function.
** cmd_name is the builtin identifier. If any element in g_builtin_tab has
** an id field which is lexicographically equal to cmd_name, the builtin
** field, which is the builtin function, is returned.
** This function can be called to execute the builtin and should be passed
** two parameters: the argument vector of the command as well as the length
** of this vector.
**
** If no builtin is found for cmd_name, NULL is returned instead.
*/

t_builtin	builtin_get(const char *cmd_name)
{
	size_t	i;

	i = 0;
	while (g_builtin_tab[i].builtin != NULL)
	{
		if (ft_strcmp(g_builtin_tab[i].id, cmd_name) == 0)
			return (g_builtin_tab[i].builtin);
		++i;
	}
	return (NULL);
}
