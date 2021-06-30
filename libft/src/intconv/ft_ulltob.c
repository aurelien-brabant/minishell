/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:46:34 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/26 00:17:30 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include "libft/core.h"

static size_t	get_nb_len(unsigned long long nb, uint8_t base)
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
** unsigned long long to base.
**
** @param	nb		=> the base number as an unsigned long long.
** @param	base	=> the base to convert in. Accepted values are 2-16.
**
** @return	a malloc-allocated string holding the representation of nb in the
** specified base.
*/

char	*ft_ulltob(unsigned long long nb, uint8_t base)
{
	char		*charset;
	size_t		len;
	size_t		i;
	char		*str;

	charset = "0123456789ABCDEF";
	len = get_nb_len(nb, base);
	i = 0;
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (0);
	while (nb)
	{
		str[i++] = charset[nb % base];
		nb /= base;
	}
	if (i == 0)
		str[i++] = '0';
	return (ft_strrev(str));
}
