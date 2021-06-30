/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_findchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 00:09:16 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 01:03:00 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"

int	ft_string_findchar(t_string_int *str, const char c)
{
	size_t	i;

	i = 0;
	while (i < str->length)
	{	
		if (str->chrs[i] == c)
			return (i);
		++i;
	}
	return (-1);
}
