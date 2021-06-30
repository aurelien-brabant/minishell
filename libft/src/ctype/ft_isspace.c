/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:34:05 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/25 22:01:45 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/types.h" 

/*
** libft implementation of isspace(3)
*/

unsigned char	ft_isspace(char c)
{
	char	*charset;

	charset = "\n\t\r\f\v ";
	while (*charset)
		if (*charset++ == c)
			return (1);
	return (0);
}
