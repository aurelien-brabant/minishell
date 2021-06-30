#include <stdlib.h>

#include "libft/core.h"
#include "libft/cstring.h"

#include "minishell/datastructure.h"

static int	resize(t_stringv *sv)
{
	char	**new_data;

	new_data = ft_calloc(sv->cap * 2 + 1, sizeof (*new_data));
	if (new_data == NULL)
		return (1);
	ft_memcpy(new_data, sv->data, sizeof (*sv->data) * sv->cap);
	free(sv->data);
	sv->data = new_data;
	sv->cap *= 2;
	return (0);
}

char	*stringv_add(t_stringv *sv, char *str)
{
	if (sv->len == sv->cap && resize(sv) != 0)
		return (NULL);
	sv->data[sv->len++] = str;
	sv->data[sv->len] = NULL;
	return (str);
}

void	stringv_del(t_stringv *sv, size_t index)
{
	size_t	i;

	i = index;
	while (i < sv->len)
	{
		sv->data[i] = sv->data[i + 1];
		++i;
	}
	--sv->len;
	sv->data[sv->len] = NULL;
}

void	stringv_destroy(t_stringv *sv)
{
	free(sv->data);
	free(sv);
}

t_stringv	*stringv_new(size_t cap)
{
	t_stringv	*sv;

	sv = ft_calloc(1, sizeof (*sv));
	if (sv == NULL)
		return (NULL);
	sv->data = ft_calloc(cap + 1, sizeof (*sv->data));
	if (sv->data == NULL)
	{
		free(sv);
		return (NULL);
	}
	sv->len = 0;
	sv->cap = cap;
	return (sv);
}
