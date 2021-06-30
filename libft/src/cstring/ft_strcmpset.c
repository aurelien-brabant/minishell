/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:01:35 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/11 21:58:12 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"

/*
** Compare two memory areas as memcmp does, but stop when the current
** equal byte is contained in *set*.
**
** @param	p1	=>	address of the beginning of the area 1.
** @param	p2	=>	address of the beginning of the area 2.
** @param	set	=>	the set of byte.
**
** USAGE EXAMPLE:
**
** ft_memcmpset("--option=myopt", "--option", "=");
** - Comparision will stop at the = sign. In this example it is used
** to verify that the option keys are identical.
**
** @return	same as memcmp(3), strcmp(3) and so on...
*/

static bool	is_in_set(const char *set, unsigned char c)
{
	const unsigned char	*uset;

	uset = (const unsigned char *)set;
	while (*uset != '\0')
		if (*uset++ == c)
			return (true);
	return (false);
}

int	ft_strcmpset(const char *s1, const char *s2, const char *set)
{
	const unsigned char	*us1;
	const unsigned char	*us2;
	bool				break_flag;

	us1 = (const unsigned char *)s1;
	us2 = (const unsigned char *)s2;
	while (*us1 != '\0')
	{
		break_flag = *us1 != *us2;
		if (is_in_set(set, *us1)
			|| is_in_set(set, *us2))
		{
			break_flag = true;
			if (us1 != (const unsigned char *)s1)
			{
				--us1;
				--us2;
			}
		}
		if (break_flag)
			break ;
		++us1;
		++us2;
	}
	return (*us1 - *us2);
}
