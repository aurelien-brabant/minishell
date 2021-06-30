/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:08:35 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/28 19:17:13 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/vector.h"
#include "libft/internal/gc_int.h"

t_gc_int	*ft_gc_new(void)
{
	t_gc_int	*gc;

	gc = malloc(sizeof (*gc));
	if (gc == NULL)
		return (NULL);
	gc->collector = ft_vector_new(10);
	if (gc->collector == NULL)
	{
		free(gc);
		return (NULL);
	}
	gc->triggers = ft_vector_new(10);
	if (gc->triggers == NULL)
	{
		free(gc);
		ft_vector_destroy(gc->collector, NULL);
	}
	return (gc);
}
