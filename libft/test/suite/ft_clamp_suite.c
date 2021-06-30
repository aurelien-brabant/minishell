#include <criterion/criterion.h>
#include "libft.h"

TestSuite(ft_clamp);

Test(ft_clamp, test_clamp_min)
{
	int	nb = 45;
	int min = 46;
	int	max = 567;

	cr_assert_eq(min, ft_clamp(nb, min, max));
}

Test(ft_clamp, test_clamp_max)
{
	int	nb = 1000;
	int min = 46;
	int	max = 567;

	cr_assert_eq(max, ft_clamp(nb, min, max));
}

Test(ft_clamp, test_clamp_min_gt_max)
{
	int	nb = 1000;
	int min = 100000;
	int	max = -3;

	cr_assert_eq(nb, ft_clamp(nb, min, max));
}
