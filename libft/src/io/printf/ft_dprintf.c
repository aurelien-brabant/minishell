/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:23:23 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 20:25:17 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/cstring.h"
#include "libft/internal/printf.h"

/*
** Initialize ft_dprintf call. Where everything starts.
*/

int	ft_dprintf(int fd, const char *fmt, ...)
{
	t_state				s;
	va_list				alst;
	t_converter			conv[TOTAL_SPEC];

	if (write(fd, NULL, 0) == -1)
		return (-1);
	s.fmt = fmt;
	va_start(alst, fmt);
	s.alst = &alst;
	s.written = 0;
	s.buf.len = 0;
	s.buf.outspec = FD_OUT;
	s.buf.dst.dfd = fd;
	init_conv(conv);
	while (*s.fmt)
		parse_fmt(&s, conv);
	flush_buf(&s);
	va_end(alst);
	return (s.written);
}
