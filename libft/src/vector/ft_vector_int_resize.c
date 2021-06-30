/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_int_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 12:58:53 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/27 00:36:37 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/internal/vector_int.h"

void	ft_vector_int_resize(t_vector_int *a)
{
	void	**new_arr;

	new_arr = ft_calloc(a->capacity * 2 + 1, sizeof(*a->vector));
	ft_memcpy(new_arr, a->vector, a->capacity * sizeof(*a->vector));
	free(a->vector);
	a->capacity *= 2;
	a->vector = new_arr;
}
