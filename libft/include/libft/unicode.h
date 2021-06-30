/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:28:57 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/23 17:04:25 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNICODE_H
# define UNICODE_H
# include "./types.h"

t_byte	*ft_encode_utf8(t_rune *r);
t_byte	ft_runelen(t_rune r);
t_byte	*ft_buf_utf8(t_byte *dst, t_rune r);

#endif
