/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_findcsubset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:46:13 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 12:05:53 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"

int	ft_string_findcsubset(t_string_int *str, const char *subset)
{
	size_t	i;
	size_t	j;
	size_t	saved;

	i = 0;
	while (i < str->length)
	{
		saved = i;
		j = 0;
		while (subset[j] != '\0' && str->chrs[i] == (unsigned char) subset[j])
		{
			++i;
			++j;
		}
		if (subset[j] == '\0')
			return (saved);
		i = saved + 1;
	}
	return (-1);
}
