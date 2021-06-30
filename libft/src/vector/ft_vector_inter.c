/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_inter.c                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:00:20 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:31:23 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"
#include "libft/vector.h"

t_vector	ft_vector_inter(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *))
{
	t_vector_int	*new;
	size_t			i;

	new = (t_vector_int *)ft_vector_new(((t_vector_int *)a1)->capacity);
	if (new == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < ((t_vector_int *)a1)->length)
	{
		if (ft_vector_linsearch(a2,
				((t_vector_int *)a1)->vector[i], cmp) != -1)
		{
			((t_vector_int *)new)->vector[new->length++]
				= ((t_vector_int *)a1)->vector[i];
		}
		++i;
	}
	return (new);
}
