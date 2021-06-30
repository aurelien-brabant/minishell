#include "libft/cstring.h"

int	ft_get_short_opt(int argc, const char **argv, const char *opstring,
		const char **optarg)
{
	static int			optind = 0;
	static const char	*ptr = "";
	char				*opchar_loc;

	*optarg = NULL;
	while (*ptr == '\0')
	{
		if (++optind >= argc)
			return (-1);
		if (argv[optind][0] == '-')
			ptr = &argv[optind][1];
	}
	opchar_loc = ft_strchr(opstring, *ptr);
	++ptr;
	if (opchar_loc == NULL)
		return ('?');
	if (opchar_loc[1] == ',' && optind + 1 < argc)
		*optarg = argv[optind + 1];
	return (*opchar_loc);
}
