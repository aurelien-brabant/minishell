#include <stdbool.h>
#include <stdio.h>

#include "minishell/lexer.h"

#include "libft/cstring.h"

char	*get_token(char **str_loc)
{
	t_token_type	toktype;
	const char		*str;
	size_t			i;
	t_chr_class		chr_class;

	if ((**str_loc) == '\0')
		return (NULL);
	str = *str_loc;
	toktype = get_token_type(get_chr_class(*str)); 
	i = 1;
	chr_class = get_chr_class(str[i]);
	while (get_chr_class_context(toktype, get_chr_class(str[i])))
		++i;
	if (toktype == get_token_type(get_chr_class(str[i])))
		++i;
	*str_loc += i;
	if (chr_class == CHR_CLASS_BLANK)
		while (get_chr_class(**str_loc) == CHR_CLASS_BLANK)
			++(*str_loc);
	return (ft_substr(str, 0, i));
}
