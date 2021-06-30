/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:21:41 by abrabant          #+#    #+#             */
/*   Updated: 2021/02/11 01:41:18 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include "../types.h"
# define ERROR -1
# define GNL_EOF 0
# define SUCCESS 1
# define BUFFER_SIZE 1000

typedef struct s_fd_item
{
	int					fd;
	char				buf[BUFFER_SIZE + 1];
	struct s_fd_item	*next;
}						t_fd_item;

int			join_rd(const char *fdbuf, char **stacked);
int			pop_ln(char *stacked, char *fdbuf, char **line);
int			init_gnl(t_fd_item **head, t_fd_item **item, int fd,
				char **stacked);
int			make_line(t_fd_item *item, char *stacked, char **line, int rdres);

t_fd_item	*get_fd_item(t_fd_item **head, int fd);
void		destroy_fd_item(t_fd_item **head, int fd);

#endif
