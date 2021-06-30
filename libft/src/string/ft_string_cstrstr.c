/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_cstrstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 23:01:24 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/14 23:35:46 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"

int	ft_string_cstrstr(t_string_int *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	while (i < haystack->length)
	{
		j = 0;
		tmp = i;
		while (i < haystack->length && needle[j] != '\0'
			&& haystack->chrs[i++] == needle[j])
			++j;
		if (needle[j] == '\0')
			return (tmp);
		i = tmp + 1;
	}
	return (-1);
}
