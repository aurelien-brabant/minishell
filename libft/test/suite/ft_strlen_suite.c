#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strlen);

Test(ft_strlen, test_basic)
{
	char	*ref = "hello world this is a string";
	size_t	reflen = strlen(ref);
	size_t	ftlen = ft_strlen(ref);

	cr_assert(reflen == ftlen, "For s=\"%s\":\nWas: \"%ld\"\nExpected: \"%ld\"", ref, ftlen, reflen);
}

Test(ft_strlen, test_empty_string)
{
	char	*ref = "";
	size_t	reflen = strlen(ref);
	size_t	ftlen = ft_strlen(ref);

	cr_assert(reflen == ftlen, "For s=\"%s\":\nWas: \"%ld\"\nExpected: \"%ld\"", ref, ftlen, reflen);
}
