/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 20:06:35 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 13:00:06 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/core.h"
#include "libft/cstring.h"

/*
** Auxiliary strchr is an implementation of strchr(3) that does not return
** the null terminating character when c is 0. The ft_strchr function could
** not be used here because this behavior is problematic.
*/

static char	*aux_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	return (0);
}

/*
** Allocates the exact amount of memory necessary to hold the trimmed version
** of str.
**
** @param	str	=> The string that will be trimmed.
** @param	set	=> the characters to trim.
**
** @return	a pointer to the first allocated byte.
*/

char	*alloc_trim(char const *str, char const *set)
{
	int		i;
	int		j;
	size_t	str_len;
	size_t	trimed_length;

	trimed_length = 0;
	str_len = ft_strlen(str);
	i = 0;
	j = str_len - 1;
	while (set && str[i] && aux_strchr(set, str[i]))
	{
		++i;
		++trimed_length;
	}
	while (set && i < j && aux_strchr(set, str[j]))
	{
		--j;
		++trimed_length;
	}
	return (ft_calloc((str_len - trimed_length) + 1, sizeof(char)));
}

/*
** Remove every character included in set from the beginning and the end of
** s1. The exact amount of memory is allocated thanks to the helper function
** alloc_trim (above).
**
** @param	s1	=> the string to trim.
** @param	s2	=> the set of characters that are going to be trimmed.
**
** @return	The trimed string, allocated by alloc_trim.
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	int		i;
	int		j;
	int		tmp;

	trimed = alloc_trim(s1, set);
	if (!trimed)
		return (0);
	i = 0;
	j = 0;
	while (set && aux_strchr(set, s1[i]))
		++i;
	while (s1[i])
	{
		tmp = i;
		while (aux_strchr(set, s1[i]) != 0)
			++i;
		if (!s1[i])
			break ;
		i = tmp;
		trimed[j++] = s1[i++];
	}
	return (trimed);
}
