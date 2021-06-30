/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_uniq.c                                    :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:45:11 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:35:02 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h" 

int	ft_vector_uniq(t_vector_int *a, int cmp(void *, void *))
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < a->length)
	{
		j = i + 1;
		while (j < a->length)
		{
			if (cmp(a->vector[i], a->vector[j]) == 0)
				return (j);
			++j;
		}
		++i;
	}
	return (-1);
}
