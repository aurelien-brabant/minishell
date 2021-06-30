/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhssfx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:01:54 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/12 15:44:42 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"

/*
** Checks if a string has a given suffix.
**
** @param	s	=> the base string.
** @param	sfx	=> the suffix to search.
**
** @return true (1) if suffix is found, false (0) otherwise.
*/

bool	ft_strhssfx(const char *s, const char *sfx)
{
	int		i;
	int		j;

	i = ft_strlen(s) - 1;
	j = ft_strlen(sfx) - 1;
	while (j >= 0 && i >= 0)
	{
		if (s[i--] != sfx[j--])
			return (false);
	}
	if (i < 0 && (j != i))
		return (false);
	return (true);
}
