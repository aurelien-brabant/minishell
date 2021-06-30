/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:30:35 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 13:00:40 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/cstring.h"
#include "libft/core.h"

/*
** Create a new string that is a substring of s, starting from index start,
** ending at index (start + len). Bounds included.
**
** @param	s		=> the base string.
** @param	start	=> the index of string the substring starts at.
**
** @return	the malloc-allocated substring, or 0 in case malloc failed.
*/

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			slen;
	size_t			sublen;
	char			*substr;

	slen = ft_strlen(s);
	if (start >= slen)
		return (0);
	if (len > slen - (start + 1))
		sublen = slen - start;
	else
		sublen = len;
	substr = ft_calloc(sublen + 1, sizeof(char));
	if (!substr)
		return (0);
	len = sublen;
	while (len)
	{
		*substr++ = s[start++];
		--len;
	}
	return (substr - sublen);
}
