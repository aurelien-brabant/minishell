/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:03:49 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 17:06:27 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/stack_int.h"

void	ft_stack_push(t_stack_int *stack, void *el)
{
	ft_vector_append(stack->data, el);
}
