/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:55:53 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/25 20:05:38 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"

unsigned char	*ft_string_at(t_string_int *str, size_t i)
{
	return (&str->chrs[i]);
}
