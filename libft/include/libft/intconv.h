/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intconv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:31:21 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/23 19:40:03 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTCONV_H
# define INTCONV_H
# include "./types.h"

char	*ft_itoa(int n);
char	*ft_lltob(long long n, unsigned char base);
char	*ft_ulltob(unsigned long long n, unsigned char base);
size_t	ft_ulllenb(unsigned long long n, t_byte base);

#endif
