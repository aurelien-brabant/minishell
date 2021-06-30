/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_destroy.c                                 :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:54:20 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/31 02:05:10 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/internal/vector_int.h"

void	ft_vector_destroy(t_vector_int *a, void (*fn)(void *el))
{
	size_t	i;

	if (a == NULL)
		return ;
	i = 0;
	if (fn != NULL)
	{
		while (i < a->length)
			fn(a->vector[i++]);
	}
	free(a->vector);
	free(a);
}
