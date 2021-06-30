/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_merge.c                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:54:15 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:32:05 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "libft/internal/vector_int.h"

static	t_vector	get_new_vector(t_vector a1, t_vector a2)
{
	t_vector_int	*new;

	new = (t_vector_int *)ft_vector_new(((t_vector_int *)a1)->capacity
			+ ((t_vector_int *)a2)->capacity);
	if (new == NULL)
	{
		return (NULL);
	}
	new->length = ((t_vector_int *)a1)->length + ((t_vector_int *)a2)->length;
	return (new);
}

t_vector	ft_vector_merge(t_vector a1, t_vector a2,
		int (*cmp)(void *el1, void *el2))
{
	t_vector_int	*new;
	size_t			i;
	size_t			j;
	size_t			k;

	i = 0;
	j = 0;
	k = 0;
	new = get_new_vector(a1, a2);
	while (i < ((t_vector_int *)a1)->length && j < ((t_vector_int *)a2)->length)
	{
		if (cmp(((t_vector_int *)a1)->vector[i],
				((t_vector_int *)a2)->vector[j]) > 0)
			new->vector[k++] = ((t_vector_int *)a2)->vector[j++];
		else
			new->vector[k++] = ((t_vector_int *)a1)->vector[i++];
	}
	while (i < ((t_vector_int *)a1)->length)
		new->vector[k++] = ((t_vector_int *)a1)->vector[i++];
	while (j < ((t_vector_int *)a2)->length)
		new->vector[k++] = ((t_vector_int *)a2)->vector[j++];
	return (new);
}
