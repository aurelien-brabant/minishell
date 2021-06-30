/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_union.c                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:57:12 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/13 16:19:47 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "libft/internal/vector_int.h"
#include "libft/cstring.h"

t_vector	ft_vector_union(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *))
{
	t_vector_int	*new;
	size_t			i;

	new = (t_vector_int *)ft_vector_new(((t_vector_int *)a1)->capacity
			+ ((t_vector_int *)a2)->capacity);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new->vector, ((t_vector_int *)a1)->vector,
		sizeof(*new->vector) * ((t_vector_int *)a1)->length);
	new->length = ((t_vector_int *)a1)->length;
	i = 0;
	while (i < ((t_vector_int *)a2)->length)
	{
		if (ft_vector_linsearch(a1, ((t_vector_int *)a2)->vector[i], cmp) == -1)
		{
			((t_vector_int *)new)->vector[new->length++]
				= ((t_vector_int *)a2)->vector[i];
		}
		++i;
	}
	return (new);
}
