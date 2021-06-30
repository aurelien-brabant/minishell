/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 21:19:26 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:31:26 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** libft implementation of memchr(3)
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sc;
	unsigned char	ch;

	sc = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*sc == ch)
			return ((void *)sc);
		++sc;
	}
	return (NULL);
}
