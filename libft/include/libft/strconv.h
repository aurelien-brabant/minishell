/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strconv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:24:42 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/10 23:55:58 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRCONV_H
# define STRCONV_H
# include "./types.h"

int			ft_atoi(const char *nptr);
long long	ft_btoll(const char *s, uint8_t base);

#endif
