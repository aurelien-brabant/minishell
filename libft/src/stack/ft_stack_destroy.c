/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:51:13 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/28 23:04:26 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/vector.h"
#include "libft/internal/stack_int.h"

void	ft_stack_destroy(t_stack_int *stack, void (*fn)(void *))
{
	if (stack == NULL)
		return ;
	ft_vector_destroy(stack->data, fn);
	free(stack);
}
