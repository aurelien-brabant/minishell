/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:30:52 by abrabant          #+#    #+#             */
/*   Updated: 2020/09/30 23:15:30 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Find the index of the first occurence of c in str.
**
** @param	str	=> the string we search in.
** @param	c	=> the character to find.
**
** @return	the index in str where c occurs for the first time, -1 if it doesn't
** occur at all.
*/

int	ft_strchri(char const *str, char const c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}
