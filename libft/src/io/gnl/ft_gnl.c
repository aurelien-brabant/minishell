/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:24:04 by abrabant          #+#    #+#             */
/*   Updated: 2020/12/28 20:12:40 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/core.h"
#include "libft/cstring.h"
#include "libft/internal/gnl.h"

int	ft_gnl(int fd, char **line)
{
	static t_fd_item	*head = 0;
	t_fd_item			*item;
	char				*stacked;
	int					rdres;

	rdres = 1;
	if (!line || init_gnl(&head, &item, fd, &stacked) == ERROR)
		return (ERROR);
	while (!ft_strchr(stacked, '\n'))
	{
		rdres = read(fd, item->buf, BUFFER_SIZE);
		if (rdres <= 0)
			break ;
		item->buf[rdres] = 0;
		if (join_rd(item->buf, &stacked) == ERROR)
			return (ERROR);
	}
	rdres = make_line(item, stacked, line, rdres);
	if (rdres == GNL_EOF)
		destroy_fd_item(&head, fd);
	return (rdres);
}

int	init_gnl(t_fd_item **head, t_fd_item **item, int fd
			, char **stacked)
{
	*stacked = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (ERROR);
	*item = get_fd_item(head, fd);
	if (!*item)
		return (ERROR);
	if ((*item)->buf[0])
		*stacked = ft_strndup((*item)->buf, ft_strlen((*item)->buf));
	else
		*stacked = ft_strndup("", 1);
	if (!*stacked)
		return (ERROR);
	return (SUCCESS);
}

int	make_line(t_fd_item *item, char *stacked, char **line, int rdres)
{
	if (rdres > 0)
		return (pop_ln(stacked, item->buf, line));
	if (rdres == 0)
	{
		*line = stacked;
		return (GNL_EOF);
	}
	free(stacked);
	return (ERROR);
}

int	join_rd(const char *fdbuf, char **stacked)
{
	char			*tmp;
	size_t			join_len;
	size_t			i;
	size_t			j;
	int				retval;

	i = 0;
	j = 0;
	join_len = ft_strlen(fdbuf) + ft_strlen(*stacked) + 1;
	retval = ERROR;
	tmp = *stacked;
	*stacked = ft_calloc(join_len, sizeof(char));
	if (*stacked)
	{
		while (tmp && tmp[j])
			stacked[0][i++] = tmp[j++];
		while (*fdbuf)
			stacked[0][i++] = *fdbuf++;
		stacked[0][i] = 0;
		retval = SUCCESS;
	}
	free((void *)tmp);
	return (retval);
}

int	pop_ln(char *stacked, char *fdbuf, char **line)
{
	char	*tmp;
	char	*nlp;
	size_t	i;
	int		retval;

	tmp = stacked;
	nlp = ft_strchr(stacked, '\n');
	i = -1;
	retval = SUCCESS;
	while (nlp[++i + 1])
		fdbuf[i] = nlp[i + 1];
	fdbuf[i] = 0;
	*line = ft_strndup(tmp, nlp - tmp);
	if (!*line)
		retval = ERROR;
	free((void *)tmp);
	return (retval);
}
