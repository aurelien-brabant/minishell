#include <criterion/criterion.h>
#include "libft/core.h"

TestSuite(ft_acmp_int);

Test(ft_acmp_int, test_equal)
{
	int	a = -34;
	int	b = -34;
	int	*ap = &a;
	int	*bp = &b;

	cr_assert(ft_acmp_int(&ap, &bp) == 0);
}

Test(ft_acmp_int, test_less_than)
{
	int	a = -345;
	int	b = -45;
	int	*ap = &a;
	int	*bp = &b;

	cr_assert(ft_acmp_int(&ap, &bp) < 0);
}

Test(ft_acmp_int, test_greater_than)
{
	int	a = 120;
	int	b = -45;
	int	*ap = &a;
	int	*bp = &b;

	cr_assert(ft_acmp_int(&ap, &bp) > 0);
}
