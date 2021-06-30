/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_sinter.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:09:46 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:34:06 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "libft/internal/vector_int.h"
#include "libft/cstring.h"

/*
** NOTE: To be clear, the way this code is organized is ugly and I know it.
** I did not find any other suitable way to code that function without
** infringing 42's norm. That's stupid code, but at least it works.
** Rework of this function without the norm restrictions is planned.
*/

static	t_vector	get_new_vector(t_vector a1)
{
	t_vector_int	*new;

	new = (t_vector_int *)ft_vector_new(((t_vector_int *)a1)->capacity);
	if (new == NULL)
	{
		return (NULL);
	}
	return (new);
}

/*
** Add the element to the new vector one time and increment both index pointers.
** Skip duplicates as we don't want to trigger this procedure another time
** for them.
*/

static void	handle_ret_zero(t_vector_int **arrs, size_t *iter,
		int (*cmp)(void *el1, void *el2))
{
	void	*tmp;

	arrs[2]->vector[arrs[2]->length] = arrs[0]->vector[iter[0]++];
	tmp = arrs[2]->vector[arrs[2]->length++];
	++iter[1];
	while (iter[0] < arrs[0]->length && cmp(arrs[0]->vector[iter[0]], tmp) == 0)
		iter[0]++;
	while (iter[1] < arrs[1]->length && cmp(arrs[1]->vector[iter[1]], tmp) == 0)
		iter[1]++;
}

t_vector	ft_vector_sinter(t_vector a1, t_vector a2,
		int (*cmp)(void *el1, void *el2))
{
	size_t			iter[2];
	t_vector_int	*arrs[3];
	int				ret;

	ft_memset(iter, 0, sizeof(iter));
	arrs[0] = (t_vector_int *)a1;
	arrs[1] = (t_vector_int *)a2;
	arrs[2] = get_new_vector(a1);
	if (arrs[2] == NULL)
		return (NULL);
	while (iter[0] < arrs[0]->length && iter[1] < arrs[1]->length)
	{
		ret = cmp(arrs[0]->vector[iter[0]], arrs[1]->vector[iter[1]]);
		if (ret > 0)
			++iter[1];
		else if (ret == 0)
			handle_ret_zero(arrs, iter, cmp);
		else
			++iter[0];
	}
	return (arrs[2]);
}
