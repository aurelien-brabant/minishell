/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:56:44 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:34:50 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/core.h"

/*
** Counts the number of words in str. A word is delimited by the c character.
**
** @param	str	=> the str that is divided into words
** @param	c	=> the delimitor character.
**
** @return (number of words + 1), including 0 termination for the string
** vector that'll be generated using getwc.
*/

static unsigned int	getwc(char const *str, char c)
{
	unsigned int	count;

	count = 0;
	if (*str && *str != c)
		++count;
	while (*str)
	{
		if (*str == c)
		{
			while (*str && *str == c)
				++str;
			if (*str)
				++count;
		}
		else
			++str;
	}
	return (count + 1);
}

/*
** Counts the number of characters from str[i] until c is found.
**
** @param	str	=> the string that is evaluated.
** @param	c	=> the single character delimitor.
** @param	i	=> the index of str we start counting from.
**
** @return	(number of characters + 1), including string null termination for
** the string that'll be generated using getlc.
*/

static unsigned int	getlc(char const *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != c)
	{
		++i;
		++count;
	}
	return (count + 1);
}

/*
** Split the string s into words, seperated by the single character c.
**
** @param	s	=> the base string.
** @param	c	=> the single character delimitor c.
**
** @return	a string vector that contains every word + ending 0 pointer.
*/

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		x;

	strs = ft_calloc(getwc(s, c), sizeof(char *));
	if (!strs)
		return (0);
	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			++i;
		if (s[i])
			strs[++j] = ft_calloc(getlc(s, c, i), sizeof(char));
		if (s[i] && strs[j])
		{
			x = 0;
			while (s[i] && s[i] != c)
				strs[j][x++] = s[i++];
		}
	}
	strs[++j] = 0;
	return (strs);
}
