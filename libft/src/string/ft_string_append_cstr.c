/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_append_cstr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:18:20 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 14:59:18 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/internal/string_int.h"

/*
** new size is newlen * 2 to predict further appends.
*/

static bool	resize(t_string_int *str, size_t newlen)
{
	uint8_t	*newchrs;
	size_t	newsize;

	newsize = sizeof(char) * newlen * 2;
	newchrs = malloc(newsize);
	if (newchrs == NULL)
		return (false);
	str->capacity = newsize;
	ft_memcpy(newchrs, str->chrs, str->length);
	free(str->chrs);
	str->chrs = newchrs;
	return (true);
}

void	ft_string_append_cstr(t_string_int *str, const char *cstr)
{
	size_t	newlen;
	size_t	i;

	newlen = str->length + ft_strlen(cstr);
	if (newlen > str->capacity && !resize(str, newlen))
		return ;
	i = 0;
	while (str->length < newlen)
		str->chrs[str->length++] = cstr[i++];
}
