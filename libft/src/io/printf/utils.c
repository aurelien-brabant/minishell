/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:09:51 by abrabant          #+#    #+#             */
/*   Updated: 2021/02/04 22:39:25 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/printf.h"
#include "libft/types.h"

/*
** This file provides utility functions to shorten and beautify the code used
** to implement printf. This is done through functions as complex macros
** are forbidden by the norm.
*/

/*
** Check if a given flag is set for the current conversion.
*/

bool	isflag(t_state *s, t_flag f)
{
	return (s->conv.flags & f);
}

void	remflag(t_state *s, t_flag f)
{
	s->conv.flags = s->conv.flags & ~f;
}

bool	ishexspec(t_state *s)
{
	return (s->conv.spec == HEXUPR_SPEC || s->conv.spec == HEXLWR_SPEC
		|| s->conv.spec == PTR_SPEC);
}

bool	is_int_conv(t_state *s)
{
	return (s->conv.spec == INT_SPEC || s->conv.spec == UINT_SPEC
		|| s->conv.spec == HEXLWR_SPEC || s->conv.spec == HEXUPR_SPEC);
}
