/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_reverse.c                                 :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:47:31 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/22 13:50:44 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"

void	ft_vector_reverse(t_vector_int *a)
{
	int		i;
	int		j;
	void	*tmp;

	i = 0;
	j = a->length - 1;
	while (i < j)
	{
		tmp = a->vector[i];
		a->vector[i++] = a->vector[j];
		a->vector[j--] = tmp;
	}
}
