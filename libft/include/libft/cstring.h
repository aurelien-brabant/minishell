/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstring.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:17:27 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/24 21:26:16 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSTRING_H
# define CSTRING_H
# include "./types.h"

/*
** MEMORY
*/

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*strrchr(const char *s, int c);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
char	*ft_strcasestr(const char *haystack, const char *needle);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
int		ft_strcmpset(const char *s1, const char *s2, const char *set);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strtok(char *str, const char *delim);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strtrim_uniq(const char *s, const char *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strinsrt(const char *insrt, const char *src, size_t index);
char	*ft_strrev(char *str);
char	*ft_strupr(char *str);
char	*ft_strlwr(char *str);
int		ft_strchri(const char *str, const char c);
bool	ft_strhsprfx(const char *s, const char *prfx);
bool	ft_strhssfx(const char *s, const char *sfx);

#endif
