/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:12:21 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/07 15:18:46 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/cstring.h"

/*
** libft implementation of FreeBSD strlcpy(3)
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	while (*src && size && i < (size - 1))
	{
		*dst++ = *src++;
		++i;
	}
	if (size > 0)
		*dst = '\0';
	return (src_len);
}
