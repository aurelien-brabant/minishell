/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:23:23 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 22:39:29 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/internal/printf.h"

/*
** Initialize ft_vsprintf call. Where everything starts.
*/

int	ft_vsprintf(char *str, const char *fmt, va_list ap)
{
	t_state				s;
	va_list				alst;
	t_converter			conv[TOTAL_SPEC];

	s.fmt = fmt;
	va_copy(alst, ap);
	s.alst = &alst;
	s.written = 0;
	s.buf.len = 0;
	s.buf.outspec = STRING_OUT;
	s.buf.dst.strout.s = str;
	s.buf.dst.strout.lim = -1;
	init_conv(conv);
	while (*s.fmt)
		parse_fmt(&s, conv);
	flush_buf(&s);
	va_end(alst);
	return (s.written);
}
