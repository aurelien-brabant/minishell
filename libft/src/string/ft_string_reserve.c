/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_reserve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:30:27 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/25 22:51:55 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/internal/string_int.h"

void	ft_string_reserve(t_string_int *str, size_t rsize)
{
	unsigned char	*newchrs;

	if (str->length > rsize)
		return ;
	newchrs = malloc(sizeof(char) * rsize);
	if (newchrs == NULL)
		return ;
	str->capacity = rsize;
	ft_memcpy(newchrs, str->chrs, sizeof(char) * str->length);
	free(str->chrs);
	str->chrs = newchrs;
}
