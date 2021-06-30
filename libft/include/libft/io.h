/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:33:15 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/29 13:18:52 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H
# include "./types.h"
# include <stdarg.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_gnl(int fd, char **line);

/*
** printf family, including "v" variants.
*/

int		ft_printf(const char *fmt, ...);
int		ft_sprintf(char *str, const char *fmt, ...);
int		ft_snprintf(char *str, size_t len, const char *fmt, ...);
int		ft_dprintf(int fd, const char *fmt, ...);
int		ft_vprintf(const char *fmt, va_list ap);
int		ft_vsprintf(char *str, const char *fmt, va_list ap);
int		ft_vsnprintf(char *str, size_t len, const char *fmt, va_list ap);
int		ft_vdprintf(int fd, const char *fmt, va_list ap);

#endif
