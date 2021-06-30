/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 00:09:36 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/08 13:30:19 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

/*
** Same as strstr(3), but ignoring the case.
** Even if strcasestr(3) is sometimes available, this is a non-standard
** extension.
*/

char	*ft_strcasestr(const char *haystack, const char *needle)
{
	size_t	i;
	char	*saved;

	saved = 0;
	while (*haystack)
	{
		saved = (char *)haystack;
		i = 0;
		while (*haystack && ft_tolower(*haystack++) == ft_tolower(needle[i]))
			++i;
		if (!needle[i])
			return (saved);
	}
	return (0);
}
