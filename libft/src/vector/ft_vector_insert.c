/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_insert.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:13:39 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 15:10:13 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/internal/vector_int.h"

void	ft_vector_insert(t_vector_int *a, void *el, size_t index)
{
	size_t	i;

	if (a->length == a->capacity)
		ft_vector_int_resize(a);
	i = a->length;
	while (i > index)
	{
		a->vector[i] = a->vector[i - 1];
		--i;
	}
	a->vector[index] = el;
	++a->length;
}
