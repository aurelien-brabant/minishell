/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_suniq.c                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:03:15 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:34:41 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"

int	ft_vector_suniq(t_vector_int *a, int cmp(void *, void *))
{
	int	i;
	int	high;

	high = a->length - 1;
	i = 0;
	while (i < high)
	{
		if (cmp(a->vector[i], a->vector[i + 1]) == 0)
			return (i + 1);
		++i;
	}
	return (-1);
}
