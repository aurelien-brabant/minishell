#include <criterion/criterion.h>
#include "libft/core.h"

TestSuite(ft_gcmp_uint);

Test(ft_gcmp_uint, test_equal)
{
	int	a = 42;
	int	b = 42;

	cr_assert(ft_gcmp_uint(&a, &b) == 0);
}

Test(ft_gcmp_uint, test_less_than)
{
	int	a = 2;
	int	b = 329493;

	cr_assert(ft_gcmp_uint(&a, &b) < 0);
}

Test(ft_gcmp_uint, test_greater_than)
{
	int	a = 1201294;
	int	b = 43242;

	cr_assert(ft_gcmp_uint(&a, &b) > 0);
}
