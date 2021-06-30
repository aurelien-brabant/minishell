/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 00:40:18 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/25 11:28:36 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include <stdlib.h>

/*
** My implementation of the realloc CONCEPT. I prefer talking about concept
** as this implementation is not following the standard one, as I have
** no access to malloc inner details. This implementation assumes a perfect
** understanding of what is done, there's no particular security checks.
**
** @param	ptr		=>	the original pointer to reallocate.
** @param	osize	=>	the size of the old memory area pointed by ptr.
** @param	nsize	=>	the size of the new memory area.
**
** @return	a pointer to the new memory area, or NULL if malloc failed.
*/

void	*ft_realloc(void *ptr, size_t osize, size_t nsize)
{
	void	*nptr;

	nptr = malloc(nsize);
	if (!nptr)
		return (NULL);
	ft_memcpy(nptr, ptr, osize);
	free(ptr);
	return (nptr);
}
