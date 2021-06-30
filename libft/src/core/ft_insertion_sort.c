/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 00:47:30 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/31 02:04:45 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"

void	ft_insertion_sort(void *mem, size_t nb_el, size_t size_el,
				int (*cmp)(void *, void *))
{
	size_t	i;
	size_t	j;
	void	*inserted;

	inserted = malloc(size_el);
	if (inserted == NULL)
		return ;
	i = 1;
	while (i < nb_el)
	{
		j = i;
		ft_memcpy(inserted, mem + (j * size_el), size_el);
		while (j > 0 && cmp(inserted, mem + (j - 1) * size_el) < 0)
		{
			ft_memcpy(mem + (j * size_el), mem + (j - 1) * size_el, size_el);
			--j;
		}
		ft_memcpy(mem + (j * size_el), inserted, size_el);
		++i;
	}
}
