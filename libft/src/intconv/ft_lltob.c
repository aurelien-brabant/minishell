/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:46:34 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/26 00:14:52 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include "libft/core.h"

static size_t	get_nb_len(long long nb, uint8_t base)
{
	size_t	count;

	count = 1;
	while (nb)
	{
		++count;
		nb /= base;
	}
	return (count);
}

/*
** long long to base.
**
** @param	nb		=> the base number as an unsigned long long.
** @param	base	=> the base to convert in. Accepted values are 2-16.
**
** @return	a malloc-allocated string holding the representation of nb in the
** specified base.
*/

char	*ft_lltob(long long nb, uint8_t base)
{
	unsigned long long	nbr;
	char				*charset;
	size_t				len;
	size_t				i;
	char				*str;

	charset = "0123456789ABCDEF";
	i = 0;
	nbr = nb;
	len = get_nb_len(nb, base) + (nb < 0);
	if (nb < 0 && ++len)
		nbr = (unsigned long long) - nb;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	while (nbr)
	{
		str[i++] = charset[nbr % base];
		nbr /= base;
	}
	if (i == 0)
		str[i++] = '0';
	if (nb < 0)
		str[i++] = '-';
	return (ft_strrev(str));
}
