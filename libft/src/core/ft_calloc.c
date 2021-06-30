/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 21:49:57 by abrabant          #+#    #+#             */
/*   Updated: 2021/02/22 21:35:25 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft/cstring.h"

/*
** libft implementation of calloc(3)
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	mem = malloc(size * nmemb);
	if (!mem)
		return (NULL);
	return (ft_memset(mem, 0, nmemb * size));
}
