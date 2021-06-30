/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:30:22 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/04 11:52:01 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H
# include "./types.h"

void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_realloc(void *ptr, size_t osize, size_t nsize);

/*
** Generic implementation of a bubble sort algorithm.
** Time complexity: best: O(n) (already sorted), worst: O(n^2)
** (in descending order).
*/

void		ft_bubble_sort(void *mem, size_t nb_el, size_t size_el,
				int (*cmp)(void *, void *));

/*
** Generic implementation of an insertion sort algorithm.
** Time complexity: best: O(n) (already sorted), worst: O(n^2) (in descending
** order).
**
** Performs a lot of right shifting, and does not provide any useful
** result until all the passes are done. This algorithm is available for
** demonstration purpose AND should NOT be used to sort vectors, but
** linked lists instead because of performance issues.
*/

void		ft_insertion_sort(void *mem, size_t nb_el, size_t size_el,
				int (*cmp)(void *, void *));

/*
** Generic implementation of a selection sort algorithm.
** Time complexity: best: O(n) (already sorted), worst: O(n^2) (in descending
** order).
*/

void		ft_selection_sort(void *mem, size_t nb_el, size_t size_el,
				int (*cmp)(void *, void *));

void		ft_quick_sort(void *arr, size_t nb_el, size_t size_el,
				int (*cmp)(void *, void *));

void		ft_merge_sort(void *arr, size_t nb_el, size_t size_el,
				int (*cmp)(void *, void *));

/*
** Perform comparison of two signed integers, in a generic context
** (using void pointers). These pointers are assumed to point to an
** integer datatype.
*/

int			ft_gcmp_int(void *int1, void *int2);

/*
** Perform comparison of two UNsigned integers, in a generic context
** (using void pointers). These pointers are assumed to point to an
** UNSIGNED integer datatype.
*/

int			ft_gcmp_uint(void *uint1, void *uint2);

/*
** Perform comparison of two signed integers, when using a signed int
** t_vector.
*/

int			ft_acmp_int(void *uint1, void *uint2);

/*
** Perform comparison of two UNsigned integers, when using a UNsigned int 
** t_vector.
*/

int			ft_acmp_uint(void *uint1, void *uint2);

long long	ft_clamp(long long nb, long long min, long long max);

int			ft_get_short_opt(int argc, const char **argv, const char *opstring,
				char **optarg);

#endif
