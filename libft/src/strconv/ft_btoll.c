/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:50:30 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/10 23:55:27 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h" 
#include "libft/cstring.h" 

/*
** base to long long
*/

long long	ft_btoll(const char *s, uint8_t base)
{
	static const char *const	set = "0123456789abcdef";
	long long					nb;					
	char						*ch;
	int8_t						sign;

	nb = 0;
	sign = 1;
	while (ft_isspace(*s))
		++s;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	ch = ft_strchr(set, ft_tolower(*s));
	while (*s++ != '\0' && ch != NULL)
	{
		nb = nb * base + (ch - set);
		ch = ft_strchr(set, ft_tolower(*s));
	}
	return (nb * sign);
}
