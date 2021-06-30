/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 09:49:00 by abrabant          #+#    #+#             */
/*   Updated: 2021/02/22 03:03:12 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include "libft/ctype.h"
#include "libft/cstring.h"

static bool	iswspace(char c)
{
	char	*set;

	set = " \n\v\r\t\f";
	return (ft_strchr(set, c) != 0);
}

/*
** libft implementation of atoi(3)
**
** underflow / overflow is handled, even if it is normally undefined.
*/

int	ft_atoi(const char *nptr)
{
	int		nb;
	int8_t	sign;
	uint8_t	n;

	nb = 0;
	sign = 1;
	while (iswspace(*nptr))
		++nptr;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr))
	{
		n = *nptr++ - 48;
		if ((uint32_t)nb * 10 + n > ((uint32_t)INT_MAX + (sign == -1)))
		{
			return (sign * INT_MAX - (sign == -1));
		}
		nb = nb * 10 + n;
	}
	return (nb * sign);
}
