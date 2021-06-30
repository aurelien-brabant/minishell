/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:50:41 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 22:12:49 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/internal/printf.h"
#include "libft/cstring.h"
#include "libft/ctype.h"

/*
** Sanitize parsing by removing incompatible flags / conversions to make
** incoming conversion process easier. Also expands stars for the width
** and precision modifiers.
*/

void	sanitize_parsing(t_state *s)
{
	if (s->conv.width == -2)
	{
		s->conv.width = va_arg(*s->alst, int);
		if (s->conv.width < 0)
		{
			s->conv.width = - (s->conv.width);
			s->conv.flags |= REV_PAD_FLAG;
		}
	}
	if (s->conv.prec == -2)
	{
		s->conv.prec = va_arg(*s->alst, int);
		if (s->conv.prec < 0)
			s->conv.prec = -1;
	}
	if (isflag(s, REV_PAD_FLAG) && isflag(s, ZERO_PAD_FLAG))
		remflag(s, ZERO_PAD_FLAG);
	if (isflag(s, BLANK_FLAG) && isflag(s, PLUS_SIGN_FLAG))
		remflag(s, BLANK_FLAG);
	if (s->conv.prec >= 0)
		remflag(s, ZERO_PAD_FLAG);
}

/*
** Parses the length specifier.
*/

void	parse_lenspec(t_state *s)
{
	if (*s->fmt == 'h' && ++s->fmt)
	{
		if (*s->fmt == 'h' && ++s->fmt)
			s->conv.lenspec = HH_LENSPEC;
		else
			s->conv.lenspec = H_LENSPEC;
	}
	else if (*s->fmt == 'l' && ++s->fmt)
	{
		if (*s->fmt == 'l' && ++s->fmt)
			s->conv.lenspec = LL_LENSPEC;
		else
			s->conv.lenspec = L_LENSPEC;
	}
}

/*
** Parses the conversion specifier. Some specifiers like 'p' and 'i' can
** be interpreted as aliases for other specifiers.
** To simplify conversion code, they are "unaliased" by this function.
*/

void	parse_spec(t_state *s)
{
	const char	*specset;
	char		*c;

	specset = "csduxXp%n";
	if (*s->fmt == '\0')
		return ;
	c = ft_strchr(specset, *s->fmt);
	if (c)
		s->conv.spec = c - specset + 1;
	else if (*s->fmt == 'i')
		s->conv.spec = INT_SPEC;
	if (s->conv.spec == PTR_SPEC)
		s->conv.lenspec = LL_LENSPEC;
	++s->fmt;
}

/*
** Main parsing function. Parses flags, width and precision and calls
** parse_lenspec and parse_spec to parse the length specifier and the
** conversion specifier.
*/

void	parse_conv(t_state *s)
{
	char		*flagset;
	char		*c;

	flagset = "#0- +";
	c = ft_strchr(flagset, *s->fmt);
	while (c)
	{
		s->conv.flags |= 1 << (c - flagset);
		s->fmt++;
		c = ft_strchr(flagset, *s->fmt);
	}
	if (*s->fmt == '*' && *s->fmt++)
		s->conv.width = -2;
	while (ft_isdigit(*s->fmt))
		s->conv.width = s->conv.width * 10 + *s->fmt++ - 48;
	if (*s->fmt == '.' && *s->fmt++)
	{
		s->conv.prec = 0;
		if (*s->fmt == '*' && *s->fmt++)
			s->conv.prec = -2;
		while (ft_isdigit(*s->fmt))
			s->conv.prec = s->conv.prec * 10 + *s->fmt++ - 48;
	}
	parse_lenspec(s);
	parse_spec(s);
}

/*
** Process each element of the format string. When a single % is found,
** calls the parse_conv function in charge of parsing the conversion
** expression.
*/

void	parse_fmt(t_state *s, const t_converter *converters)
{
	if (*s->fmt == '%' && *(s->fmt + 1))
	{
		++s->fmt;
		s->conv.flags = DEFAULT_FLAG;
		s->conv.prec = -1;
		s->conv.width = 0;
		s->conv.spec = DEFAULT_SPEC;
		s->conv.lenspec = DEFAULT_LENSPEC;
		s->conv.isneg = false;
		s->conv.iszero = false;
		parse_conv(s);
		sanitize_parsing(s);
		if (s->conv.spec != DEFAULT_SPEC)
			converters[s->conv.spec](s);
		return ;
	}
	store_in_buf(s, s->fmt, 1);
	++s->fmt;
}
