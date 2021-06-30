#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strncmp);

Test(ft_strncmp, test_diff)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello boy";
	int			ref;
	int			ft;

	ref = strncmp(s1, s2, 9);
	ft = ft_strncmp(s1, s2, 9);

	cr_assert(ref > 0 && ft > 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strncmp, test_equal)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello world";
	int			ref;
	int			ft;

	ref = strncmp(s1, s2, 12);
	ft = ft_strncmp(s1, s2, 12);

	cr_assert(ref == ft, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strncmp, test_equal_n)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello world";
	int			ref;
	int			ft;

	ref = strncmp(s1, s2, 3);
	ft = ft_strncmp(s1, s2, 3);

	cr_assert(ref == ft, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strncmp, test_not_equal_n)
{
	const char	*s1 = "HellO world";
	const char	*s2 = "Hello world";
	int			ref;
	int			ft;

	ref = strncmp(s1, s2, 5);
	ft = ft_strncmp(s1, s2, 5);

	cr_assert(ref < 0 && ft < 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strncmp, test_unequal_last)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello worlD";
	int			ref;
	int			ft;

	ref = strncmp(s1, s2, 11);
	ft = ft_strncmp(s1, s2, 11);

	cr_assert(ref > 0 && ft > 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strncmp, test_zero_len)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello world";
	int			ref;
	int			ft;

	ref = strncmp(s1, s2, 0);
	ft = ft_strncmp(s1, s2, 0);

	cr_assert(ref == ft, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}
