/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_replacechar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 23:23:54 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 14:59:05 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"

void	ft_string_replacechar(t_string_int *str, const char orig,
			const char repchar)
{
	size_t	i;

	i = 0;
	while (i < str->length)
	{
		if (str->chrs[i] == orig)
			str->chrs[i] = repchar;
		++i;
	}
}
