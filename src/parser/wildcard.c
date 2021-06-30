#include <dirent.h>
#include <stdio.h>

#include "libft/cstring.h"

#include "minishell/datastructure.h"

static void	init_candidates(t_stringv *candidates)
{
	DIR				*dir;
	struct dirent	*item;

	dir = opendir(".");
	if (dir == NULL)
		return ;
	while (1)
	{
		item = readdir(dir);
		if (item == NULL)
			break ;
		if (ft_strcmp(item->d_name, ".") != 0
				&& ft_strcmp(item->d_name, "..") != 0)
			stringv_add(candidates, item->d_name);
	}
}

static void	eliminate(t_stringv *sv, const char c, size_t len)
{
	size_t	i;
	
	i = 0;
	while (i < sv->len)
	{
		if (ft_strncmp(sv->data[i], s, len + 1))
			stringv_del(sv, i);
		++i;
	}
}

void	expand_wildcard(const char *s)
{
	t_stringv	*candidates;	
	char		quote;
	size_t		i;

	candidates = stringv_new(10);
	init_candidates(candidates);
	quote = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (quote == s[i])
			quote = 0;
		else if ((s[i] == '"' || s[i] == '\'') && ft_strchr(s + 1, s[i]))
			quote = s[i];
		else if (!quote && s[i] == '*')
			// wilcard
		else
			eliminate();
	}
}
