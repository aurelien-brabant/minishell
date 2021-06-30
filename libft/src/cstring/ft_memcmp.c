/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 21:35:00 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:32:48 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** libft implementation of memcmp(3)
*/

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	unsigned char	*mem1;
	unsigned char	*mem2;

	mem1 = (unsigned char *)s1;
	mem2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (*mem1++ == *mem2++ && --n)
		;
	return (*(--mem1) - *(--mem2));
}
