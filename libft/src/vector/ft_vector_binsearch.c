/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_binsearch.c                               :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:43:40 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/21 19:55:33 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"

int	ft_vector_binsearch(t_vector_int *a, void *ref,
						int cmp(void *ref, void *el))
{
	int	high;
	int	low;
	int	mid;
	int	ret;

	low = 0;
	high = a->length - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		ret = cmp(ref, a->vector[mid]);
		if (ret == 0)
		{
			return (mid);
		}
		if (ret > 0)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return (-1);
}
