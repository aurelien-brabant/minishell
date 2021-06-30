/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 02:05:58 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 02:24:06 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"

int	ft_string_cmp(t_string_int *str1, t_string_int *str2)
{
	size_t	i;

	i = 0;
	while (i < str1->length && i < str2->length
		&& str1->chrs[i] == str2->chrs[i])
		++i;
	return (str1->chrs[i] - str2->chrs[i]);
}
