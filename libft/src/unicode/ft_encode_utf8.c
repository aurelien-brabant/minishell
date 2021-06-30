/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_utf8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:48:53 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 22:56:26 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/types.h"
#include "libft/core.h"

static size_t	get_alloc_size(t_rune *r)
{
	size_t	count;

	count = 0;
	while (*r)
		count += ft_runelen(*r++);
	return (count);
}

/*
** encodes an vector of runes into UTF-8 and put the encoded result in
** a malloc-ed vector of bytes.
**
** @param	r	=>	a pointer to the start of the rune vector.
**
** @return	the malloc-ed string.
*/

t_byte	*ft_encode_utf8(t_rune *r)
{
	t_byte	*enc_ptr;
	t_byte	*enc;

	enc = ft_calloc(get_alloc_size(r) + 1, sizeof(t_byte));
	enc_ptr = enc;
	if (!enc)
		return (0);
	while (*r)
	{
		enc = ft_buf_utf8(enc, *r) + ft_runelen(*r);
		++r;
	}
	return (enc_ptr);
}
