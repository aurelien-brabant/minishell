/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:10:00 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/13 16:18:33 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/internal/merge_sort_int.h"
#include "libft/cstring.h"

/*
** For norm sake (again ...)
*/

static void	copy_and_increment(void *tmp, void **ptr, size_t size_el)
{
	ft_memcpy(tmp, *ptr, size_el);
	*ptr += size_el;
}

static void	merge(void *low, void *mid, void *high, t_merge_sort *ms)
{
	void	*i;
	void	*j;
	void	*tmp;

	i = low;
	j = mid + ms->size_el;
	tmp = ms->tmp;
	while (i <= mid && j <= high)
	{
		if (ms->cmp(i, j) < 0)
			copy_and_increment(tmp, &i, ms->size_el);
		else
			copy_and_increment(tmp, &j, ms->size_el);
		tmp += ms->size_el;
	}
	if (i <= mid)
		ft_memcpy(tmp, i, mid - i + ms->size_el);
	if (j <= high)
		ft_memcpy(tmp, j, high - j + ms->size_el);
	ft_memcpy(low, ms->tmp, high - low + ms->size_el);
}

static void	rec_mergesort(void *arr, size_t low, size_t high, t_merge_sort *ms)
{
	size_t	mid;

	if (low < high)
	{
		mid = (low + high) / 2;
		rec_mergesort(arr, low, mid, ms);
		rec_mergesort(arr, mid + 1, high, ms);
		merge(arr + low * ms->size_el, arr + mid * ms->size_el,
			arr + high * ms->size_el, ms);
	}
}

void	ft_merge_sort(void *arr, size_t nb_el, size_t size_el,
		int (*cmp)(void *, void *))

{
	t_merge_sort	ms;

	ms.tmp = malloc(size_el * nb_el);
	if (ms.tmp == NULL)
		return ;
	ms.cmp = cmp;
	ms.size_el = size_el;
	rec_mergesort(arr, 0, nb_el - 1, &ms);
	free(ms.tmp);
}
