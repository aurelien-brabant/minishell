/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:41:57 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/25 21:21:12 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_INT_H
# define STRING_INT_H
# include <stdint.h>
# include <stddef.h>

/* Internal header for the string data structure */

typedef struct s_string_int
{
	unsigned char	*chrs;
	size_t			length;
	size_t			capacity;
}	t_string_int;

#endif
