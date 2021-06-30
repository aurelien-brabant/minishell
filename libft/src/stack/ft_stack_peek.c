/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_peek.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:52:44 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:57:08 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/stack_int.h"

void	*ft_stack_peek(t_stack_int *stack)
{
	return (ft_vector_get(stack->data, ft_vector_length(stack->data) - 1));
}
