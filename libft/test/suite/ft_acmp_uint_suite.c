#include <criterion/criterion.h>
#include "libft/core.h"

TestSuite(ft_acmp_uint);

Test(ft_acmp_uint, test_equal)
{
	int	a = 42;
	int	b = 42;
	int	*ap = &a;
	int	*bp = &b;

	cr_assert(ft_acmp_uint(&ap, &bp) == 0);
}

Test(ft_acmp_uint, test_less_than)
{
	int	a = 5;
	int	b = 42;
	int	*ap = &a;
	int	*bp = &b;

	cr_assert(ft_acmp_uint(&ap, &bp) < 0);
}

Test(ft_acmp_uint, test_greater_than)
{
	int	a = 120;
	int	b = 2;
	int	*ap = &a;
	int	*bp = &b;

	cr_assert(ft_acmp_uint(&ap, &bp) > 0);
}
