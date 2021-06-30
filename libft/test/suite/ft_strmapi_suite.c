#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strmapi);

/*
** The map function will replace the mapped char by the next ascii character.
*/

static char	next_ascii(unsigned int i, char c)
{
	(void)i;
	return (c + 1);
}

/*
** Use the iterator and add it to the current character.
*/

static char	next_inth_ascii(unsigned int i, char c)
{
	return (c + i);
}

Test(ft_strmapi, test_basic)
{
	char			refbuf[] = "Hello world!";		
	const char		*base = "Hello world!";
	char			*mapped = NULL;
	size_t			reflen = strlen(refbuf);

	/* Simulate the expected behavior */
	for (size_t j = 0; j < reflen; ++j)
	{
		++refbuf[j];
	}
	mapped = ft_strmapi(base, &next_ascii);
	cr_expect(strcmp(refbuf, mapped) == 0, "Was:\"%s\"\nExpected:\"%s\"", refbuf, mapped);
	free(mapped);
}

Test(ft_strmapi, test_index)
{
	char			refbuf[] = "Hello world!";		
	const char		*base = "Hello world!";
	char			*mapped = NULL;
	size_t			reflen = strlen(refbuf);

	/* Simulate the expected behavior */
	for (size_t j = 0; j < reflen; ++j)
	{
		refbuf[j] = next_inth_ascii(j, refbuf[j]);
	}
	mapped = ft_strmapi(base, &next_inth_ascii);
	cr_expect(strcmp(refbuf, mapped) == 0, "Was:\"%s\"\nExpected:\"%s\"", refbuf, mapped);
	free(mapped);
}
