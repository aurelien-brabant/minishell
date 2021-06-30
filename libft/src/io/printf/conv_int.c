/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:29:07 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/13 16:19:00 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/internal/printf.h"
#include "libft/strconv.h"
#include "libft/intconv.h"
#include "libft/cstring.h"
#include "libft/ctype.h"

/*
** @UTIL
**
** Bufferize the given unsigned long long number in the ft_printf buffer.
** The number is bufferized in the specified base, taking set as the default
** charset.
**
** @param	s		=> a pointer to the ft_printf global state.
** @param	n		=> the extracted integer.
** @param	base	=> the arithmetic base.
*/

static void	buf_int(t_state *s, unsigned long long n, unsigned char base)
{
	char			*set;
	t_byte			c;

	set = "0123456789abcdef";
	if (n >= base)
		buf_int(s, n / base, base);
	c = set[n % base];
	if (s->conv.spec == HEXUPR_SPEC)
		c = ft_toupper(c);
	store_in_buf(s, (char *) & c, 1);
}

static void	buf_alt_form(t_state *s, bool iszero)
{
	if (ishexspec(s) && ((isflag(s, ALT_FORM_FLAG) && !iszero)
			|| s->conv.spec == PTR_SPEC))
	{
		if (s->conv.spec == HEXUPR_SPEC)
			store_in_buf(s, "0X", 2);
		else
			store_in_buf(s, "0x", 2);
	}
}

/*
** @UTIL
**
** Get the field length of the conversion, in order to apply field width when
** needed.
**
** @param	s		=> a pointer to the ft_printf global state.
** @param	nlen	=> The "length" of the extracted integer.
** @param	iszero	=> Whether or not the extracted integer is equal to zero.
**					Special considerations may be applied if true.
**
** @return	the field length used by the buf_field_width function.
*/

static size_t	get_flen(t_state *s, size_t nlen, bool iszero)
{
	size_t	flen;

	flen = nlen - (iszero && s->conv.prec == 0);
	flen += (ishexspec(s) && ((isflag(s, ALT_FORM_FLAG) && !iszero)
				|| s->conv.spec == PTR_SPEC)) * 2;
	flen += (s->conv.isneg || isflag(s, BLANK_FLAG)
			|| isflag(s, PLUS_SIGN_FLAG));
	if (s->conv.prec > (int)nlen)
		flen += s->conv.prec - nlen;
	return (flen);
}

/*
** @EXPORTED
**
** The conversion function used for every integer conversion specifier (diuxXp)
**
** @param	s	=> a pointer to the ft_printf global state.
*/

void	conv_int(t_state *s)
{
	unsigned long long	n; 	
	size_t				nlen;
	int					prec;

	n = extract_int(s);
	nlen = ft_ulllenb(n, 10 + (ishexspec(s) * 6));
	if (!isflag(s, ZERO_PAD_FLAG) && !isflag(s, REV_PAD_FLAG))
		buf_field_width(s, get_flen(s, nlen, n == 0));
	if (s->conv.isneg)
		store_in_buf(s, "-", 1);
	else if (isflag(s, PLUS_SIGN_FLAG))
		store_in_buf(s, "+", 1);
	else if (isflag(s, BLANK_FLAG))
		store_in_buf(s, " ", 1);
	buf_alt_form(s, n == 0);
	if (isflag(s, ZERO_PAD_FLAG))
		buf_field_width(s, get_flen(s, nlen, n == 0));
	prec = s->conv.prec;
	while (prec-- > (int)nlen)
		store_in_buf(s, "0", 1);
	if (!(n == 0 && s->conv.prec == 0))
		buf_int(s, n, 10 + (ishexspec(s) * 6));
	if (isflag(s, REV_PAD_FLAG))
		buf_field_width(s, get_flen(s, nlen, n == 0));
}
