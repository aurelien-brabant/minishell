#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_memcmp);

Test(ft_memcmp, test_equal)
{
	const char	*s1 = "stringéstring2";
	const char	*s2 = "string2string1";
	int			ref = 0;
	int			ft = 0;

	ref = memcmp(s1, s2, 6);
	ft = ft_memcmp(s1, s2, 6);

	cr_assert(ref == ft, "For s1=\"%s\"; s2=\"%s\"; n=%d:\nWas: %d\nExpected: %d\nWARNING: only the sign of the return value is defined. See the man.", s1, s2, 6, ft, ref);
}

Test(ft_memcmp, test_differs)
{
	const char	*s1 = "stringéstring2";
	const char	*s2 = "string2string1";
	int			ref = 0;
	int			ft = 0;

	ref = memcmp(s1, s2, 56);
	ft = ft_memcmp(s1, s2, 56);

	cr_assert(ft > 0, "For s1=\"%s\"; s2=\"%s\"; n=%d:\nWas: %d\nExpected: %d\nWARNING: only the sign of the return value is defined. See the man.", s1, s2, 56, ft, ref);
}

Test(ft_memcmp, test_zero_len)
{
	const char	*s1 = "stringéstring2";
	const char	*s2 = "string2string1";
	int			ref = 0;
	int			ft = 0;

	ref = memcmp(s1, s2, 0);
	ft = ft_memcmp(s1, s2, 0);

	cr_assert(ft == ref, "For s1=\"%s\"; s2=\"%s\"; n=%d:\nWas: %d\nExpected: %d\nWARNING: only the sign of the return value is defined. See the man.", s1, s2, 0, ft, ref);
}

Test(ft_memcmp, test_last_differs)
{
	const char	*s1 = "string2string2";
	const char	*s2 = "stringéstring1";
	int			ref = 0;
	int			ft = 0;

	ref = memcmp(s1, s2, 7);
	ft = ft_memcmp(s1, s2, 7);

	cr_assert(ft < 0, "For s1=\"%s\"; s2=\"%s\"; n=%d:\nWas: %d\nExpected: %d\nWARNING: only the sign of the return value is defined. See the man.", s1, s2, 0, ft, ref);
}
