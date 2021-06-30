/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 13:24:30 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:59:19 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/types.h"
#include "libft/cstring.h"

/*
** libft implementation of strrchr(3)
**
** Behaves like my libft strnstr(3) implementation, except that we search the
** last occurence of a single character and that if this character is null,
** the terminator is returned. It is indeed returned, so performing a cat -e
** on the output should display a "^@" character, which is the representation
** of a non printable null byte.
*/

char	*ft_strrchr(const char *s, int c)
{
	long long	i;

	i = ft_strlen(s);
	while (i >= 0)
		if (s[i--] == c)
			return ((char *)&s[i + 1]);
	return (NULL);
}
