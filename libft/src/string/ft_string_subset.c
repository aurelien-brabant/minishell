/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_subset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:48:05 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 13:00:45 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/internal/string_int.h"

/*
** Only check for low >= high, but doesn't ensure they're valid indexes.
*/

t_string_int	*ft_string_subset(t_string_int *str, size_t low, size_t high)
{
	t_string_int	*new;

	if (low >= high)
		return (NULL);
	new = malloc(sizeof (*new));
	if (new == NULL)
		return (NULL);
	new->chrs = malloc(sizeof (char) * high - low);
	if (new->chrs == NULL)
	{
		free(new);
		return (NULL);
	}
	new->capacity = high - low;
	new->length = 0;
	while (low < high)
		new->chrs[new->length++] = str->chrs[low++];
	return (new);
}
