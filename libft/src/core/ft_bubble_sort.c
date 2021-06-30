/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant </var/mail/abrabant>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:28:44 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/31 01:59:16 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft/cstring.h"

/*
** Always returns true to trick the norm
*/

static bool	swap(void *mem, void *tmp, size_t size_el)
{
	ft_memcpy(tmp, mem, size_el);
	ft_memcpy(mem, mem + size_el, size_el);
	ft_memcpy(mem + size_el, tmp, size_el);
	return (true);
}

void	ft_bubble_sort(void *mem, size_t nb_el, size_t size_el,
		int (*cmp)(void *, void *))
{
	size_t	i;
	size_t	j;
	bool	swaped_flag;
	void	*tmp;
	void	*cur;

	i = 0;
	tmp = malloc(size_el);
	if (tmp == NULL)
		return ;
	while (i < nb_el)
	{
		swaped_flag = false;
		cur = mem;
		j = 0;
		while (j++ < nb_el - i - 1)
		{
			if (cmp(cur, cur + size_el) > 0)
				swaped_flag = swap(cur, tmp, size_el);
			cur += size_el;
		}
		if (!swaped_flag)
			break ;
		++i;
	}
}
