/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:53:28 by abrabant          #+#    #+#             */
/*   Updated: 2020/11/07 15:45:29 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** Put a single character on a given fd.
**
** @param	c	=> the single character to output.
** @param	fd	=> the fd to output on.
*/

void	ft_putchar_fd(char c, int fd)
{
	c = (unsigned char)c;
	write(fd, &c, 1);
}
