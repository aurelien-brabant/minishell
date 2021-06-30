/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_isempty.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:17:25 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/27 14:57:17 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft/internal/stack_int.h"

bool	ft_stack_isempty(t_stack_int *stack)
{
	return (ft_vector_length(stack->data) == 0);
}
