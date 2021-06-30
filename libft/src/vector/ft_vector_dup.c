/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_dup.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 18:23:16 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/13 16:19:19 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/vector.h"
#include "libft/internal/vector_int.h"

t_vector	ft_vector_dup(t_vector a)
{
	t_vector_int	*new;

	new = (t_vector_int *)ft_vector_new(((t_vector_int *)a)->capacity);
	if (new == NULL)
	{
		return (NULL);
	}
	new->length = ((t_vector_int *)a)->length;
	ft_memcpy(new->vector, ((t_vector_int *)a)->vector,
		sizeof(*new->vector) * new->length);
	return (new);
}
