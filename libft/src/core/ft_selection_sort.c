/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selection_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant </var/mail/abrabant>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:33:43 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/01 15:17:39 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"

static void	swap(void *mem, void *mem2, void *tmp, size_t size_el)
{
	ft_memcpy(tmp, mem, size_el);
	ft_memcpy(mem, mem2, size_el);
	ft_memcpy(mem2, tmp, size_el);
}

void	ft_selection_sort(void *mem, size_t nb_el, size_t size_el,
				int (*cmp)(void *, void *))
{
	void	*tmp;
	size_t	i;
	size_t	j;
	size_t	k;

	tmp = malloc(size_el);
	if (tmp == NULL)
		return ;
	i = 0;
	while (i < nb_el)
	{
		k = i;
		j = i + 1;
		while (j < nb_el)
		{
			if (cmp(mem + j * size_el, mem + k * size_el) < 0)
				k = j;
			++j;
		}
		swap(mem + i * size_el, mem + k * size_el, tmp, size_el);
		++i;
	}
}
