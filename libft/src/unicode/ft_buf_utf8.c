/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_utf8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:03:42 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 23:12:27 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"

/*
** Encodes a rune in UTF=8 outputing the result in the passed buffer.
**
** @param	dst	=>	the buffer to output the encoded string.
** @param	r	=>	the rune to be encoded.
**
** @return	a pointer to the first encoded byte in dst.
*/

t_byte	*ft_buf_utf8(t_byte *dst, t_rune r)
{
	size_t	i;

	i = 0;
	if (ft_runelen(r) == 1)
		dst[i++] = (t_byte)r;
	else
	{
		if (ft_runelen(r) == 2)
			dst[i++] = (r >> 0x06) | 0xC0;
		if (ft_runelen(r) == 3)
		{
			dst[i++] = (r >> 0xC) | 0xE0;
			dst[i++] = ((r >> 0x6) & 0x3F) | 0x80;
		}
		if (ft_runelen(r) == 4)
		{
			dst[i++] = (r >> 18) | 0xF0;
			dst[i++] = ((r >> 12) & 0x3F) | 0x80;
			dst[i++] = ((r >> 6) & 0x3F) | 0x80;
		}
		dst[i++] = (r & 0x3F) | 0x80;
	}
	dst[i] = 0;
	return (dst);
}
