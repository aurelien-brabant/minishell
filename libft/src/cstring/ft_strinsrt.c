/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 23:15:38 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/21 23:36:11 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/core.h"
#include "libft/cstring.h"

/*
** Duplicates a string while inserting another string at a specific position in
** it.
**
** @param	insrt	=> the string to insert. If 0, behavior is undefined.
** @param	src		=> the source string to duplicate and insert in. If 0,
** behavior is undefined.
** @param	index	=> the index to insert (inclusive).
**
** @return	the new string, 0 if malloc fails.
*/

char	*ft_strinsrt(const char *insrt, const char *src, size_t index)
{
	size_t	alloc_size;
	char	*str;
	size_t	i;

	i = 0;
	alloc_size = ft_strlen(insrt) + ft_strlen(src);
	str = ft_calloc(alloc_size + 1, sizeof(char));
	if (!str)
		return (0);
	while (i < index)
		str[i++] = *src++;
	while (*insrt)
		str[i++] = *insrt++;
	while (*src)
		str[i++] = *src++;
	return (str);
}
