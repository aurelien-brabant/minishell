/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:48:24 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/25 21:11:23 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/printf.h"

void	init_conv(t_converter *conv)
{
	conv[CHAR_SPEC] = &conv_char;
	conv[STR_SPEC] = &conv_str;
	conv[INT_SPEC] = &conv_int;
	conv[UINT_SPEC] = &conv_int;
	conv[HEXLWR_SPEC] = &conv_int;
	conv[HEXUPR_SPEC] = &conv_int;
	conv[PTR_SPEC] = &conv_int;
	conv[PCT_SPEC] = &conv_pct;
	conv[CUR_WRITTEN_SPEC] = &conv_cur_written;
}
