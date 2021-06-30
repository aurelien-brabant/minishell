#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strcmp);

Test(ft_strcmp, test_diff)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello boy";
	int			ref;
	int			ft;

	ref = strcmp(s1, s2);
	ft = ft_strcmp(s1, s2);

	cr_assert(ref > 0 && ft > 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strcmp, test_equal)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello world";
	int			ref;
	int			ft;

	ref = strcmp(s1, s2);
	ft = ft_strcmp(s1, s2);

	cr_assert(ref == ft, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strcmp, test_diff_first)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "hello world";
	int			ref;
	int			ft;

	ref = strcmp(s1, s2);
	ft = ft_strcmp(s1, s2);

	cr_assert(ref < 0 && ft < 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strcmp, test_diff_last)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "Hello worlD";
	int			ref;
	int			ft;

	ref = strcmp(s1, s2);
	ft = ft_strcmp(s1, s2);

	cr_assert(ref > 0 && ft > 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strcmp, test_empty_s1)
{
	const char	*s1 = "";
	const char	*s2 = "Hello world";
	int			ref;
	int			ft;

	ref = strcmp(s1, s2);
	ft = ft_strcmp(s1, s2);

	cr_assert(ref < 0 && ft < 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strcmp, test_empty_s2)
{
	const char	*s1 = "Hello world";
	const char	*s2 = "";
	int			ref;
	int			ft;

	ref = strcmp(s1, s2);
	ft = ft_strcmp(s1, s2);

	cr_assert(ref > 0 && ft > 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}

Test(ft_strcmp, test_equal_empty)
{
	const char	*s1 = "";
	const char	*s2 = "";
	int			ref;
	int			ft;

	ref = strcmp(s1, s2);
	ft = ft_strcmp(s1, s2);

	cr_assert(ref == ft, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%d\"\nExpected:\"%d\"WARNING: only the sign of the return value is defined.", s1, s2, ft, ref);
}
