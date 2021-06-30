/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:34:41 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 12:42:59 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** libft implementation of strcpy(3)
*/

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dst_ptr;

	dst_ptr = dest;
	while (*src)
		*dest++ = src++;
	*dest = 0;
	return (dst_ptr);
}
