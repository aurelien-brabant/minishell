/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_new_cstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:38:15 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 14:59:42 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/internal/string_int.h"
#include "libft/cstring.h"

t_string_int	*ft_string_new_cstr(const char *cstring)
{
	t_string_int	*str;
	size_t			i;
	size_t			cstring_len;

	str = malloc(sizeof (*str));
	if (str == NULL)
		return (NULL);
	cstring_len = ft_strlen(cstring);
	str->length = cstring_len;
	str->capacity = cstring_len;
	str->chrs = malloc(sizeof(char) * str->length);
	if (str->chrs == NULL)
		return (NULL);
	i = 0;
	while (i < str->length)
	{
		str->chrs[i] = cstring[i];
		++i;
	}
	return (str);
}
