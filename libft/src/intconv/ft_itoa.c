/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:50:19 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/26 00:00:23 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include "libft/core.h"

static char	*strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
	}
	return (str);
}

static size_t	intlen(int nb)
{
	size_t	count;

	count = 1;
	while (nb / 10)
	{
		++count;
		nb /= 10;
	}
	return (count);
}

/*
** Parse integer to string
**
** @param	n	=> the integer number
**
** @return the string representation of the integer.
*/

char	*ft_itoa(int n)
{
	long		nb;
	size_t		nlen;
	size_t		i;
	char		*nb_str;

	nb = n;
	i = 0;
	if (n < 0)
		nb = nb * -1;
	nlen = intlen(n);
	nb_str = ft_calloc(nlen + 1 + (n < 0), sizeof(char));
	ft_memset(nb_str, '0', nlen + (n < 0));
	if (!nb_str)
		return (0);
	while (nb)
	{
		nb_str[i++] = nb % 10 + 48;
		nb /= 10;
	}
	if (n < 0)
		nb_str[i++] = '-';
	return (strrev(nb_str));
}
