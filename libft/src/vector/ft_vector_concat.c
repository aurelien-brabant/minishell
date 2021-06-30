/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_concat.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:20:53 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/13 16:19:34 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include "libft/vector.h"
#include "libft/internal/vector_int.h"

t_vector	ft_vector_concat(t_vector a1, t_vector a2)
{
	t_vector_int	*new;

	new = (t_vector_int *)ft_vector_new(((t_vector_int *)a1)->capacity
			+ ((t_vector_int *)a2)->capacity);
	if (new == NULL)
	{
		return (NULL);
	}
	new->length = ((t_vector_int *)a1)->length + ((t_vector_int *)a2)->length;
	ft_memcpy(new->vector, ((t_vector_int *)a1)->vector,
		sizeof(*new->vector) * ((t_vector_int *)a1)->length);
	ft_memcpy(new->vector + ((t_vector_int *)a1)->length,
		((t_vector_int *)a2)->vector,
		sizeof(*new->vector) * ((t_vector_int *)a2)->length);
	return (new);
}
