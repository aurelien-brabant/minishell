/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:15:12 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 20:24:46 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/printf.h"
#include "libft/cstring.h"
#include "libft/unicode.h"
#include "libft/intconv.h"

static size_t	get_utf8_field_len(t_state *s)
{
	va_list	lstcpy;
	t_rune	*ra;
	size_t	flen;

	if (s->conv.prec >= 0)
		return (s->conv.prec);
	va_copy(lstcpy, *s->alst);
	if (s->conv.spec == CHAR_SPEC)
		flen = ft_runelen(va_arg(lstcpy, t_rune));
	else
	{
		ra = va_arg(lstcpy, t_rune *);
		flen = 0;
		while (*ra)
			flen += ft_runelen(*ra++);
	}
	va_end(lstcpy);
	return (flen);
}

/*
** Get the current field length of the converted item before having applied
** any width correction. This calculation is used by the buf_field_width
** function to know the necessary amount of padding to add (if any).
*/

static size_t	get_text_field_len(t_state *s)
{
	va_list	lstcpy;
	size_t	flen;
	char	*str;

	flen = 0;
	if (s->conv.spec == CHAR_SPEC)
		return (1);
	if (s->conv.prec >= 0)
		return (s->conv.prec);
	va_copy(lstcpy, *s->alst);
	str = va_arg(lstcpy, char *);
	va_end(lstcpy);
	if (!str)
		return (0);
	return (ft_strlen(str));
}

size_t	get_field_len(t_state *s)
{
	int	flen;

	flen = 0;
	if (s->conv.spec == CHAR_SPEC || s->conv.spec == STR_SPEC)
	{
		if (s->conv.lenspec == L_LENSPEC)
			flen = get_utf8_field_len(s);
		else
			flen = get_text_field_len(s);
	}
	return (flen);
}

/*
** Add the right amount of padding, which can be made of spaces (' ' only) or
** zeros depending on the flag combination provided. There's no direct
** management of padding position, this function needs to be called at the
** right time, i.e when the padding is expected.
*/

void	buf_field_width(t_state *s, size_t flen)
{
	char	padc;

	padc = ' ';
	if (s->conv.width <= (int)flen)
		return ;
	if (isflag(s, ZERO_PAD_FLAG))
		padc = '0';
	while (s->conv.width-- > (int)flen)
		store_in_buf(s, &padc, 1);
}
