/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:17:38 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/27 23:10:46 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/internal/vector_int.h"
#include "libft/cstring.h"

void	ft_vector_append(t_vector_int *a, void *el)
{
	if (a->length == a->capacity)
		ft_vector_int_resize(a);
	a->vector[a->length++] = el;
	a->vector[a->length] = NULL;
}
