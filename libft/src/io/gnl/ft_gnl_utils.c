/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 14:03:36 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 20:13:01 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/internal/gnl.h"

t_fd_item	*get_fd_item(t_fd_item **head, int fd)
{
	t_fd_item	*cur;
	t_fd_item	*new;

	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		if (!cur->next)
			break ;
		cur = cur->next;
	}
	new = malloc(sizeof(*new));
	if (!new)
		return (0);
	new->fd = fd;
	new->buf[0] = 0;
	new->next = 0;
	if (!cur)
		*head = new;
	else
		cur->next = new;
	return (new);
}

void	destroy_fd_item(t_fd_item **head, int fd)
{
	t_fd_item	*cur;
	t_fd_item	*last;

	cur = *head;
	last = 0;
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (!last)
				*head = cur->next;
			else
				last->next = cur->next;
			free(cur);
			return ;
		}
		last = cur;
		cur = cur->next;
	}
}
