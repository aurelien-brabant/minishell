#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strndup);

Test(ft_strndup, test_basic)
{
	char	*ref = "Hello world";
	char	*ftdup = 0;
	char	*refdup = 0;
	size_t	n = 5; 

	ftdup = ft_strndup(ref, n);
	refdup = ft_strndup(ref, n);
	/* Will produce a crash if duped memory is not readable. */
	ftdup[0] = ftdup[0];
	cr_expect(strcmp(refdup, ftdup) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, ftdup, refdup);
	free(ftdup);
	free(refdup);
}

Test(ft_strndup, test_zero_len)
{
	char	*ref = "Hello world";
	char	*ftdup = 0;
	char	*refdup = 0;
	size_t	n = 0; 

	ftdup = ft_strndup(ref, n);
	refdup = ft_strndup(ref, n);
	/* Will produce a crash if duped memory is not readable. */
	ftdup[0] = ftdup[0];
	cr_expect(strcmp(refdup, ftdup) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, ftdup, refdup);
	free(ftdup);
	free(refdup);
}

Test(ft_strndup, test_oversized_len)
{
	char	*ref = "Hello world";
	char	*ftdup = 0;
	char	*refdup = 0;
	size_t	n = 546; 

	ftdup = ft_strndup(ref, n);
	refdup = ft_strndup(ref, n);
	/* Will produce a crash if duped memory is not readable. */
	ftdup[0] = ftdup[0];
	cr_expect(strcmp(refdup, ftdup) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, ftdup, refdup);
	free(ftdup);
	free(refdup);
}
