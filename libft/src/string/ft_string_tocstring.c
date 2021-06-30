/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_tocstring.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:55:08 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/25 16:01:26 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/internal/string_int.h"

char	*ft_string_tocstring(t_string_int *str)
{
	char	*cstr;
	size_t	i;

	cstr = malloc(str->length + 1);
	if (cstr == NULL)
		return (cstr);
	i = 0;
	while (i < str->length)
	{
		cstr[i] = str->chrs[i];
		++i;
	}
	cstr[i] = '\0';
	return (cstr);
}
