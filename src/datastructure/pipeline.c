#include <stdlib.h>

#include "libft/core.h"
#include "libft/cstring.h"

#include "minishell/datastructure.h"
#include "minishell/error.h"

static int	resize(t_pipeline *pipeline)
{
	t_command	*new_data;

	new_data = ft_calloc(pipeline->cap * 2, sizeof (*new_data));
	if (new_data == NULL)
		return (1);
	ft_memcpy(new_data, pipeline->data,
		pipeline->cap * sizeof (*pipeline->data));
	free(pipeline->data);
	pipeline->data = new_data;
	pipeline->cap *= 2;
	return (0);
}

void	pipeline_destroy(t_pipeline *pipeline)
{
	size_t	i;

	i = 0;
	while (i < pipeline->len)
	{
		redirv_destroy(pipeline->data[i].rv);
		stringv_destroy(pipeline->data[i].sv);
		++i;
	}
	free(pipeline->data);
	free(pipeline);
}

/*
** If the redirection vector and/or the string vector is not allocated
** properly, NULL is returned to indicate the error.
** Same thing for the resize operation.
*/

t_command	*pipeline_add(t_pipeline *pipeline, size_t id)
{
	t_command	*cmd;

	if (pipeline->len == pipeline->cap && resize(pipeline) != 0)
		return (NULL);
	cmd = &pipeline->data[pipeline->len];
	cmd->id = id;
	cmd->rv = redirv_new(REDIRV_DEFAULT_CAP);
	cmd->sv = stringv_new(STRINGV_DEFAULT_CAP);
	if (cmd->rv == NULL || cmd->sv == NULL)
		return (NULL);
	pipeline->len++;
	return (cmd);
}

t_pipeline	*pipeline_new(size_t cap)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof (*pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->data = ft_calloc(cap, sizeof(*pipeline->data));
	if (pipeline->data == NULL)
	{
		free(pipeline);
		return (NULL);
	}
	pipeline->len = 0;
	pipeline->cap = cap;
	return (pipeline);
}
