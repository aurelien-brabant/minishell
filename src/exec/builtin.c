#include "libft/cstring.h"

#include "minishell/exec.h"

static const struct s_builtin_entry
{
	const char	*id;
	t_builtin	builtin;
}	g_builtin_tab[] = {
	{
		.id = "exit",
		.builtin = fn_exit,
	},
	{
		.id = "cd",
		.builtin = fn_cd,
	},
	{
		.id = "export",
		.builtin = fn_export,
	},
	{
		.id = "unset",
		.builtin = fn_unset
	},
	{
		.id = "echo",
		.builtin = fn_echo,
	},
	{
		.id = "pwd",
		.builtin = fn_pwd,
	},
	{
		.id = NULL,
		.builtin = NULL,
	}
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
	}
	return (NULL);
}
