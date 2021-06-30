/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 12:19:03 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/10 12:06:56 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/io.h"

/*
** libft implementation of memset(3)
*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*byte_set;

	byte_set = (unsigned char *)s;
	while (n > 0)
	{
		*byte_set++ = c;
		--n;
	}
	return (s);
}
