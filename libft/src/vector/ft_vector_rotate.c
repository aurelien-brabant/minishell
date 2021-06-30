/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_rotate.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:19:49 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:32:54 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"

static void	rotate_one_left(t_vector_int *a)
{
	int		i;
	int		high;
	void	*rotated;

	i = 0;
	rotated = a->vector[i];
	high = a->length - 1;
	while (i < high)
	{
		a->vector[i] = a->vector[i + 1];
		++i;
	}
	a->vector[i] = rotated;
}

static void	rotate_one_right(t_vector_int *a)
{
	int		i;
	void	*rotated;

	i = a->length - 1;
	rotated = a->vector[i];
	while (i > 0)
	{
		a->vector[i] = a->vector[i - 1];
		--i;
	}
	a->vector[i] = rotated;
}

void	ft_vector_rotate(t_vector_int *a, char rotatedir, size_t offset)
{
	while (offset > 0)
	{
		if (rotatedir == -1)
			rotate_one_left(a);
		if (rotatedir == 1)
			rotate_one_right(a);
		--offset;
	}
}
