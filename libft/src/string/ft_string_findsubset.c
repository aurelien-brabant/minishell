/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_subset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:30:11 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 12:32:57 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"

int	ft_string_findsubset(t_string_int *str, t_string_int *subset)
{
	size_t	i;
	size_t	j;
	size_t	saved;

	i = 0;
	while (i < str->length)
	{
		saved = i;
		j = 0;
		while (subset->chrs[j] != '\0' && str->chrs[i] == subset->chrs[j])
		{
			++i;
			++j;
		}
		if (subset->chrs[j] == '\0')
			return (saved);
		i = saved + 1;
	}
	return (-1);
}
