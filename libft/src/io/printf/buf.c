/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:42:51 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/25 00:10:58 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "libft/cstring.h"
#include "libft/internal/printf.h"

/*
** In my ft_printf, there's no dynamic memory allocation, everything is
** stored in a buffer on the stack, which is to be flushed to stdout when
** full or when libft/internal/printf.has finished its work.
*/

/*
** Stores the given string in the print buffer. If buffer overflow is
** encountered, prevents it and flush the buffer.
*/

void	store_in_buf(t_state *s, const char *str, size_t n)
{
	while (n--)
	{
		if (s->buf.len >= PRINTF_BUF)
			flush_buf(s);
		(s->buf.str)[s->buf.len++] = *str++;
	}
}

/*
** Flushes the printf buffer to stdout.
** Add the written characters to the s.written variable used to keep track
** of total output count.
** Resets the length of the printf buffer.
*/

void	flush_to_str(t_state *s)
{
	long long	*lim;
	char		**str;

	lim = &(s->buf.dst.strout.lim);
	str = &(s->buf.dst.strout.s);
	if (!str || !lim || *lim == -2 || *lim == 0)
		return ;
	if (*lim >= 0 && (long long)(s->written + s->buf.len) >= *lim)
	{
		ft_memcpy(*str, s->buf.str, (s->written + s->buf.len - *lim));
		*str += (s->written + s->buf.len - *lim);
		*lim = -2;
	}
	else
	{
		ft_memcpy(*str, s->buf.str, s->buf.len);
		*str = *str + s->buf.len;
	}
	**str = '\0';
}

void	flush_buf(t_state *s)
{
	if (s->buf.outspec == FD_OUT)
	{
		write(s->buf.dst.dfd, s->buf.str, s->buf.len);
	}
	else if (s->buf.outspec == STRING_OUT)
		flush_to_str(s);
	s->written += s->buf.len;
	s->buf.len = 0;
}
