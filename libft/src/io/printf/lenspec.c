/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenspec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:43:09 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 22:11:15 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/printf.h"

/*
** Utility functions used to handle length specifiers such as in
** %hhd, %hd, %ld, %lld, and so on.
*/

/*
** UTIL
**
** Take an argument from the variadic argument list, treating it as
** a signed integer, which size depends on the specified length specifiers
** (if any).
**
** @param	lspec	=> the length specifier.
** @param	alst	=> a pointer to the targeted va_list.
**
** @return	a long long int, as a max-signed value.
*/

static long long	extract_signed(t_lenspec lspec, va_list *alst)
{
	long long	nb;

	if (lspec == HH_LENSPEC)
		nb = (char)va_arg(*alst, int);
	else if (lspec == H_LENSPEC)
		nb = (short)va_arg(*alst, int);
	else if (lspec == L_LENSPEC)
		nb = va_arg(*alst, long);
	else if (lspec == LL_LENSPEC)
		nb = va_arg(*alst, long long);
	else
		nb = va_arg(*alst, int);
	return (nb);
}

/*
** @UTIL
**
** Take an argument from the variadic argument list, treating it as
** an unsigned integer, which size depends on the specified length specifiers
** (if any).
**
** @param	lspec	=> the length specifier.
** @param	alst	=> a pointer to the targeted va_list.
**
** @return an unsigned long long int, as a max-unsigned value.
*/

static unsigned long long	extract_unsigned(t_lenspec lspec, va_list *alst)
{
	unsigned long long	nb;

	if (lspec == HH_LENSPEC)
		nb = (unsigned char)va_arg(*alst, int);
	else if (lspec == H_LENSPEC)
		nb = (unsigned short)va_arg(*alst, int);
	else if (lspec == L_LENSPEC)
		nb = va_arg(*alst, unsigned long);
	else if (lspec == LL_LENSPEC)
		nb = va_arg(*alst, unsigned long long);
	else
		nb = va_arg(*alst, unsigned int);
	return (nb);
}

/*
** @EXPORTED
**
** Extract the current argument in the va_list as an integer, which type
** is determined by the specified length specifier (if any).
** If the extracted int is a negative integer, it is transformed in
** unsigned for code harmonization, and the s->conv.isneg flag is set
** to true. If it is zero, the s->conv.iszero flag is set to true, as
** a integer value can lead to very special cases.
**
** @param	s	=> a pointer to the ft_printf global state.
*/

unsigned long long	extract_int(t_state *s)
{
	unsigned long long	n;
	long long			tmp;

	if (s->conv.spec == INT_SPEC)
	{
		tmp = extract_signed(s->conv.lenspec, s->alst);
		if (tmp < 0)
		{
			n = -tmp;
			s->conv.isneg = true;
		}
		else
			n = tmp;
	}
	else
		n = extract_unsigned(s->conv.lenspec, s->alst);
	if (!n)
		s->conv.iszero = true;
	return (n);
}
