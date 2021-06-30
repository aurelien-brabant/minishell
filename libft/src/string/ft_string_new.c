/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 23:18:36 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/14 23:12:41 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/internal/string_int.h"

t_string_int	*ft_string_new(size_t capacity)
{
	t_string_int	*str;

	str = malloc(sizeof (*str));
	if (str == NULL)
		return (NULL);
	str->chrs = malloc(sizeof (unsigned char) * capacity);
	if (str->chrs == NULL)
	{
		free(str);
		return (NULL);
	}
	str->length = 0;
	str->capacity = capacity;
	return (str);
}
