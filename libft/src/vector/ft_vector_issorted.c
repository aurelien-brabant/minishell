/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_issorted.c                                :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:09:47 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:31:43 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft/internal/vector_int.h"

bool	ft_vector_issorted(t_vector_int *a, int (*cmp)(void *el1, void *el2))
{
	int	high;
	int	i;

	i = 0;
	high = a->length - 1;
	while (i < high)
	{
		if (cmp(a->vector[i], a->vector[i + 1]) > 0)
			return (false);
		++i;
	}
	return (true);
}
