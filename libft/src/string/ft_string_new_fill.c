/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_new_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:13:58 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/25 22:47:39 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"
#include <stddef.h>
#include <stdlib.h>

t_string_int	*ft_string_new_fill(size_t n, const char c)
{
	t_string_int	*str;
	size_t			i;

	str = malloc(sizeof (*str));
	if (str == NULL)
		return (NULL);
	str->chrs = malloc(sizeof(char) * n);
	if (str->chrs == NULL)
		return (NULL);
	str->length = n;
	str->capacity = n;
	i = 0;
	while (i < str->length)
		str->chrs[i++] = c;
	return (str);
}
