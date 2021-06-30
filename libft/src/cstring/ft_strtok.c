/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 00:15:24 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/05 00:44:13 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/types.h"

static bool	is_delim(unsigned char c, const char *delim)
{
	const unsigned char	*delim_set;

	delim_set = (const unsigned char *)delim;
	while (*delim_set)
		if (c == *delim_set++)
			return (true);
	return (false);
}

char	*ft_strtok(char *str, const char *delim)
{
	static unsigned char	*str_ptr;
	unsigned char			*start;

	if (str)
		str_ptr = (unsigned char *)str;
	start = str_ptr;
	while (*str_ptr)
	{
		while (is_delim(*str_ptr, delim))
			*str_ptr++ = '\0';
		if (str_ptr != start && *(str_ptr - 1) == '\0' && *str_ptr)
			return ((char *)start);
		if (*str_ptr)
			++str_ptr;
	}
	if (*start != '\0')
		return ((char *)start);
	return (NULL);
}
