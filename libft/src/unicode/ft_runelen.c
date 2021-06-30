/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_runelen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:15:13 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/23 17:06:37 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"

/*
** Evaluates the length of a rune, i.e its wordsize as encoded in UTF-8.
**
** @param	r	=>	the rune.
**
** @return	the number of bytes that'll be necessary to hold the UTF-8
** representation of the given rune.
*/

t_byte	ft_runelen(t_rune r)
{
	if (r >= 0x10000)
		return (4);
	if (r >= 0x0800)
		return (3);
	if (r >= 0x0080)
		return (2);
	return (1);
}
