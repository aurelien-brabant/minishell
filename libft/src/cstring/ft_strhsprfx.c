/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhsprfx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:19:31 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/12 14:24:40 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"

bool	ft_strhsprfx(const char *s, const char *prfx)
{
	return (ft_strnstr(s, prfx, ft_strlen(prfx)) == s);
}
