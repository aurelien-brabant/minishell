/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:04:03 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/01 15:18:00 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libft/cstring.h"

/*
** This is not really allowed by the norm, but I think it's better than
** using a structure for quicksort lul.
*/

static void	*g_tmpbuf = NULL;

static void	swap(void *el1, void *el2, size_t size_el)
{
	ft_memcpy(g_tmpbuf, el1, size_el);
	ft_memcpy(el1, el2, size_el);
	ft_memcpy(el2, g_tmpbuf, size_el);
}

static void	*partition(void *low, void *high, size_t size_el,
		int (*cmp)(void *, void *))
{
	void	*max;
	void	*pivot;

	pivot = low;
	max = high;
	while (low < high)
	{
		while (low <= max && cmp(low, pivot) <= 0)
			low += size_el;
		while (cmp(high, pivot) > 0)
			high -= size_el;
		if (low < high)
			swap(low, high, size_el);
	}
	swap(pivot, high, size_el);
	return (high);
}

static void	qsort_int(void *low, void *high, size_t size_el,
		int (*cmp)(void *, void *))
{
	void	*part;

	if (low < high)
	{
		part = partition(low, high, size_el, cmp);
		qsort_int(low, part - size_el, size_el, cmp);
		qsort_int(part + size_el, high, size_el, cmp);
	}
}

void	ft_quick_sort(void *arr, size_t nb_el, size_t size_el,
		int (*cmp)(void *, void *))
{
	g_tmpbuf = malloc(size_el);
	if (g_tmpbuf == NULL)
		return ;
	qsort_int(arr, arr + (nb_el - 1) * size_el, size_el, cmp);
	free(g_tmpbuf);
}
