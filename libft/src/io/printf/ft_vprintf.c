/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:23:23 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 20:26:44 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/cstring.h"
#include "libft/internal/printf.h"

/*
** Initialize ft_vprintf call. Where everything starts.
*/

int	ft_vprintf(const char *fmt, va_list ap)
{
	va_list				alst;
	t_state				s;
	t_converter			conv[TOTAL_SPEC];

	va_copy(alst, ap);
	s.fmt = fmt;
	s.alst = &alst;
	s.written = 0;
	s.buf.len = 0;
	s.buf.outspec = FD_OUT;
	s.buf.dst.dfd = STDOUT_FILENO;
	init_conv(conv);
	while (*s.fmt)
		parse_fmt(&s, conv);
	flush_buf(&s);
	va_end(alst);
	return (s.written);
}
