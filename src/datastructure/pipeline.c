#include <stdlib.h>

#include "libft/core.h"
#include "libft/cstring.h"

#include "minishell/datastructure.h"

static void	resize(t_pipeline *pipeline)
{
	t_command	*new_data;

	new_data = ft_calloc(pipeline->cap * 2, sizeof (*new_data));
	if (new_data == NULL)
		return ;
	ft_memcpy(new_data, pipeline->data,
			pipeline->cap * sizeof (*pipeline->data));
	free(pipeline->data);
	pipeline->data = new_data;
	pipeline->cap *= 2;
}

void		pipeline_destroy(t_pipeline *pipeline)
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

t_command	*pipeline_add(t_pipeline *pipeline, size_t id)
{
	t_command	*cmd;

	if (pipeline->len == pipeline->cap)
		resize(pipeline);
	cmd = &pipeline->data[pipeline->len];
	cmd->id = id;
	cmd->rv = redirv_new(REDIRV_DEFAULT_CAP);
	cmd->sv = stringv_new(STRINGV_DEFAULT_CAP);
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
