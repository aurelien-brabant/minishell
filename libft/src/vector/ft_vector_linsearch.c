/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_linsearch.c                               :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:08:27 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 13:17:33 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"

int	ft_vector_linsearch(t_vector_int *a, void *ref,
						int cmp(void *ref, void *el))
{
	size_t	i;
	void	*tmp;

	i = 0;
	while (i < a->length)
	{
		if (cmp(ref, a->vector[i]) == 0)
		{
			if (i > 0)
			{
				tmp = a->vector[i];
				a->vector[i] = a->vector[i - 1];
				a->vector[i - 1] = tmp;
			}
			return (i);
		}
		++i;
	}
	return (-1);
}
