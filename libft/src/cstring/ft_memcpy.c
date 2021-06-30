/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 13:45:36 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:30:25 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** libft implementation of ft_memcpy(3)
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destc;
	unsigned char		*srcc;

	destc = (unsigned char *)dest;
	srcc = (unsigned char *)src;
	if (!dest && !src)
		return (0);
	while (n--)
	{
		*destc++ = *srcc++;
	}
	return (dest);
}
