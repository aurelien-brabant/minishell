#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/core.h"

#include "minishell/datastructure.h"

static void	redirv_resize(t_redirv *redirv)
{
	t_redir	*new_data;

	new_data = ft_calloc(redirv->cap * 2, sizeof(*redirv->data));
	if (new_data == NULL)
		return ;
	ft_memcpy(new_data, redirv->data, sizeof (*new_data) * redirv->cap);
	free(redirv->data);
	redirv->cap *= 2;
	redirv->data = new_data;
}

t_redirv	*redirv_new(size_t cap)
{
	t_redirv	*redirv;

	redirv = ft_calloc(1, sizeof (*redirv));
	if (redirv == NULL)
		return (NULL);
	redirv->data = ft_calloc(cap, sizeof(*redirv->data));
	if (redirv->data == NULL)
	{
		free(redirv);
		return (NULL);
	}
	redirv->cap = cap;
	redirv->len = 0;
	return (redirv);
}

t_redir	*redirv_add(t_redirv *redirv, t_redir_type type)
{
	if (redirv->len == redirv->cap)
		redirv_resize(redirv);
	redirv->data[redirv->len].type = type;
	return (&redirv->data[redirv->len++]);
}

void	redirv_destroy(t_redirv *redirv)
{
	free(redirv->data);
	free(redirv);
}
