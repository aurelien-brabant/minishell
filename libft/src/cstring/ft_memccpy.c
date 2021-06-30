/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 13:54:16 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:30:52 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** libft implementation of memccpy(3)
*/

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;

	s = (unsigned char *)src;
	if (!n)
		return (0);
	d = (unsigned char *)dest;
	*d = *s++;
	while (*d++ != (unsigned char)c && --n)
		*d = *s++;
	if (*(d - 1) == (unsigned char)c)
		return ((void *)d);
	return (0);
}
