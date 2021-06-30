/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:22:06 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/07 15:42:18 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"

/*
** Loop on a string and duplicate it while applying changes to each character
** using the given 'f' function.
**
** @param	s	=> the string to map on.
** @param	f	=> the function that'll apply changes, taking the index and
** the corresponding character as an argument.
**
** @return	the new string, resulting from successive applications of 'f'.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapped;
	unsigned int	i;

	i = 0;
	mapped = ft_strdup(s);
	if (!mapped)
		return (0);
	while (f && mapped[i])
	{
		mapped[i] = f(i, mapped[i]);
		++i;
	}
	return (mapped);
}
