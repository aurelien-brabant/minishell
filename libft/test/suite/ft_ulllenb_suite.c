#include <criterion/criterion.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_ulllenb);

Test(ft_ulllenb, test_basic)
{
	unsigned long long	n = 4544224;
	size_t				exp = 7;
	size_t				ft = ft_ulllenb(n, 10);

	cr_assert(ft == exp, "For n=%lld; base 10:\nWas: %ld\nExpected: %ld", n, ft, exp);
}

Test(ft_ulllenb, test_hex)
{
	unsigned long long	n = 0xFFFFFFF;
	size_t				exp = 7;
	size_t				ft = ft_ulllenb(n, 16);

	cr_assert(ft == exp, "For n=%lld; base 16:\nWas: %ld\nExpected: %ld", n, ft, exp);
}

Test(ft_ulllenb, test_zero_bin)
{
	unsigned long long	n = 0;
	size_t				exp = 1;
	size_t				ft = ft_ulllenb(n, 2);

	cr_assert(ft == exp, "For n=%lld; base 2:\nWas: %ld\nExpected: %ld", n, ft, exp);
}

Test(ft_ulllenb, test_max)
{
	unsigned long long	n = ULLONG_MAX;
	size_t				exp = 20;
	size_t				ft = ft_ulllenb(n, 10);

	cr_assert(ft == exp, "For n=%lld; base 8:\nWas: %ld\nExpected: %ld", n, ft, exp);
}
