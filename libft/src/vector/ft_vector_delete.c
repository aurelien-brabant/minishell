/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:55:15 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/27 00:18:20 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"

void	ft_vector_delete(t_vector_int *a, size_t index, void (*fn)(void *el))
{
	size_t	i;

	i = a->length - 1;
	if (fn != NULL)
		fn(a->vector[index]);
	while (index < i)
	{
		a->vector[index] = a->vector[index + 1];
		++index;
	}
	a->vector[index] = NULL;
	--a->length;
}
