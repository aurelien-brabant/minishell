#include <criterion/criterion.h>
#include "libft/core.h"

TestSuite(ft_gcmp_int);

Test(ft_gcmp_int, test_equal)
{
	int	a = -34;
	int	b = -34;

	cr_assert(ft_gcmp_int(&a, &b) == 0);
}

Test(ft_gcmp_int, test_less_than)
{
	int	a = -345;
	int	b = 5;

	cr_assert(ft_gcmp_int(&a, &b) < 0);
}

Test(ft_gcmp_int, test_greater_than)
{
	int	a = 120;
	int	b = -45;

	cr_assert(ft_gcmp_int(&a, &b) > 0);
}
