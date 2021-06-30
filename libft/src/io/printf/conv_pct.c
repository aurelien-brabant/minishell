/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_pct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 23:03:58 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/25 14:54:17 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/printf.h"

/*
** @EXPORTED
**
** Conversion function used for % specifier.
**
** NOTE: % is defined as a specifier, but there's no standard info
** about whether or not it is made compatible with the minimum field length
** padding. According to my tests, padding is enabled on BSD-based OSes while
** it is not the case on Linux.
** Because this project is to be evaluated on MacOS, I decided to implement
** like BSD does, even if it seems to be undefined behaviour.
**
** @param	s	=> a pointer to the ft_printf global state.
*/

void	conv_pct(t_state *s)
{
	if (!isflag(s, REV_PAD_FLAG))
		buf_field_width(s, 1);
	store_in_buf(s, "%", 1);
	if (isflag(s, REV_PAD_FLAG))
		buf_field_width(s, 1);
}
