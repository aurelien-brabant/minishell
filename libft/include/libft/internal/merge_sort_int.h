/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_int.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:13:06 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/02 17:38:45 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_SORT_INT_H
# define MERGE_SORT_INT_H
# include <stddef.h>

typedef struct s_merge_sort
{
	void	*tmp;
	size_t	size_el;
	int		(*cmp)(void *el1, void *el2);
}	t_merge_sort;

#endif
