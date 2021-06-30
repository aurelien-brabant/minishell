/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:26:39 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/22 21:47:21 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/vector_int.h"

void	*ft_vector_get(t_vector_int *a, size_t index)
{
	if (index >= a->length)
		return (NULL);
	return (a->vector[index]);
}
