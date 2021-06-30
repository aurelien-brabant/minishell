/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 21:16:44 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:33:27 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/cstring.h"

/*
** libft implementation of memmove(3)
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*src_byte;
	unsigned char		*dest_byte;

	src_byte = (unsigned char *)src;
	dest_byte = (unsigned char *)dest;
	if (src_byte < dest_byte)
	{
		while (n--)
			dest_byte[n] = src_byte[n];
	}
	else
	{
		ft_memcpy(dest_byte, src_byte, n);
	}
	return (dest);
}
