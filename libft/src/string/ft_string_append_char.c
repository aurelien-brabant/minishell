#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/internal/string_int.h"

static bool	resize(t_string_int *str, size_t newlen)
{
	unsigned char	*newchrs;
	size_t			newsize;

	newsize = sizeof(char) * newlen * 2;
	newchrs = malloc(newsize);
	if (newchrs == NULL)
		return (false);
	str->capacity = newsize;
	ft_memcpy(newchrs, str->chrs, str->length);
	free(str->chrs);
	str->chrs = newchrs;
	return (true);
}

void	ft_string_append_char(t_string_int *str, const char c)
{
	if (str->length == str->capacity)
		resize(str, str->length + 1);
	str->chrs[str->length++] = c;
}
