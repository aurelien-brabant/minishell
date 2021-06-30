/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:37:29 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/25 00:31:04 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/printf.h"
#include "libft/cstring.h"
#include "libft/unicode.h"

/*
** @EXPORTED
**
** Conversion function used for the %c specifier.
** %lc is handled.
**
** @param	s	=> a pointer to the ft_printf global state.
*/

void	conv_char(t_state *s)
{
	t_byte	buf[5];
	size_t	flen;

	flen = 1;
	ft_memset(buf, 0, 5);
	if (s->conv.lenspec == L_LENSPEC)
	{
		flen = ft_strlen((char *)ft_buf_utf8(buf, va_arg(*s->alst, t_rune)));
		if (flen == 0)
			store_in_buf(s, "\0", 1);
	}
	else
		buf[0] = (t_byte)va_arg(*s->alst, int);
	if (!isflag(s, REV_PAD_FLAG))
		buf_field_width(s, flen);
	store_in_buf(s, (char *)buf, flen);
	if (isflag(s, REV_PAD_FLAG))
		buf_field_width(s, flen);
}
