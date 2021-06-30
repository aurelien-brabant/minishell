/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:18:12 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/11 12:26:26 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include "libft/core.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = ft_calloc(n + 1, sizeof(char));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, n + 1);
	return (dup);
}
