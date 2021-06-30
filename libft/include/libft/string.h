/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:41:21 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/15 09:36:46 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H
# include <stdbool.h>
# include <stddef.h>
# include "libft/internal/string_int.h"

/* abstraction */
typedef void *t_string;

/*
** Create a new empty t_string object with a defined capacity.
*/

t_string		ft_string_new(size_t capacity);

/*
** Create a new t_string object, using a null terminated C-string for
** initialization. The size of the t_string object will be strlen(cstring).
*/

t_string		ft_string_new_cstr(const char *cstring);

/*
** Create a new t_string object of size n and fill this string with the
** character c.
*/

t_string		ft_string_new_fill(size_t n, const char c);

/*
** Output a string on a given file descriptor. Returns the number of characters
** written, or -1 if an error occured. The return value is the one returned by
** the write syscall, see write(3) for more informations.
*/

int				ft_string_output(t_string str, int fd);

/*
** Convert the string represented by str into a C null terminated version
** of it. This string is allocated by malloc, and therefore needs to be freed
** if required.
*/

char			*ft_string_tocstring(t_string str);

/*
** Parse a string into it's integer equivalent, stored in a long long
** datatype. The string representation can be expressed in a particular base,
** from base 2 to base 16. The expected charset for a base 16 is
** "0123456789ABCDEF" or "0123456789abcdef".
**
** err is going to be set to true if any parsing error occurs.
*/

long long		ft_string_btoll(t_string_int *str, unsigned char base,
					bool *err);
/*
** Compare str and str2 lexicographically. Behaves like strcmp(3).
*/

int				ft_string_cmp(t_string str, t_string str2);

/*
** Append the content of str2 to str. The content of str2 is leaved unchanged,
** while a copy of str2 is added as the end of str.
** No additional dynamic memory allocation is done, and only str1 is modified.
*/

void			ft_string_append(t_string str, t_string str2);

/*
** Append a string terminated by a null byte, also called C string, to the
** str t_string object. No new t_string object is created, so nothing is
** returned.
*/

void			ft_string_append_cstr(t_string str, const char *cstr);

void			ft_string_append_char(t_string str, const char c);

/*
** Get the address of the char at index i of str.
*/

unsigned char	*ft_string_at(t_string str, size_t i);

/*
** Reserve additional storage for a future use. For example, if the string
** is planned to grow at some point, especially multiple times, it can be better
** to manually reserve more storage to avoid too many reallocations.
** The sole capacity is modified. The length/size of the string is not, and
** reserving less data than the string currently occupies is not permitted.
*/

void			ft_string_reserve(t_string str, size_t i);

/*
** Replace every occurence of char orig by repchar
*/

void			ft_string_replacechar(t_string str, const char orig,
					const char repchar);

/*
** Search linearily for the first occurence of character c in string str.
** Return the index of it if it is found, -1 otherwise.
**
** Time complexity: up to O(n).
*/

int				ft_string_findchar(t_string str, const char c);

/*
** Find if str contains a given subset, represented as a traditional C
** string, null terminated.
** The index of the first char of the subset in str is returned if subset
** is found, -1 otherwise.
*/

int				ft_string_findcsubset(t_string str, const char *subset);

/*
** Find if str contains a given subset, represented as a t_string object.
** The index of the first char of the subset in str is returned if subset
** is found, -1 otherwise.
*/

int				ft_string_findsubset(t_string str, t_string subset);

/*
** Make an attempt to find the C-like string needle into the t_string haystack.
**
** If needle is present at least one time in haystack, the index of its first
** character is returned. -1 is returned if there's no occurence of needle in
** haystack.
**
** NOTE: the use of a t_string object allows the use of null bytes in haystack
** as standard characters, but it will never be compared positively with the
** ending null byte of needle due to the fact needle is supposed to be encoded
** in a C-like fashion, where the null byte is used to mean string termination.
*/

int				ft_string_cstrstr(t_string_int *haystack, const char *needle);

/*
** Substitute all occurences of the C string *from* by *to*, creating a new
** t_string object holding this substituted version. 
** *haystack* remains unchanged.
*/

t_string_int	*ft_string_csubst(t_string str, const char *from,
					const char *to);

/*
** Extract a subset from a string and create a new t_string object to contain
** it. low and high are the boundaries of the subset in the string. low IS
** INCLUSIVE while high is EXCLUSIVE. These values must be valid indexes,
** otherwise this is considered as undefined behaviour.
*/

t_string		ft_string_subset(t_string str, size_t low, size_t high);

t_string		ft_string_split(t_string str, const char *sep);

/*
** Get the number of characters in the string
*/

size_t			ft_string_length(t_string str);

void			ft_string_set_length(t_string_int *s, size_t length);

/*
** Get the length of a string. Returns the same value than ft_string_length.
*/

size_t			ft_string_size(t_string str);

/*
** Return the allocated storage (in bytes) for str.
*/

size_t			ft_string_capacity(t_string str);

/*
** Destroy a t_string object, freeing memory allocated for it.
*/

t_string		ft_string_destroy(t_string str);

/*
** Shortcut function to destroy an vector returned by ft_string_split
*/

void			ft_string_destroy_split(void *split);

#endif
