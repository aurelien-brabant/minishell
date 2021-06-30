/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:42:53 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/07 16:22:22 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

char	*ft_strlwr(char *str)
{
	char	*str_ptr;

	str_ptr = str;
	while (*str)
	{
		*str = ft_tolower(*str);
		++str;
	}
	return (str_ptr);
}
