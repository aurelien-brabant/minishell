#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_putnbr_fd);

Test(ft_putnbr_fd, test_basic, .init = cr_redirect_stdout)
{
	const char	*ref = "12249242142242152424164223";
	const int	nbs[] = {
		12,
		249242,
		142242,
		152424,
		16422,
		3,
		0,
	};
	for (size_t i = 0; nbs[i]; ++i)
		ft_putnbr_fd((int)nbs[i], 1);
	cr_assert_stdout_eq_str(ref);
}

Test(ft_putnbr_fd, test_negative, .init = cr_redirect_stdout)
{
	const char	*ref = "-12-249242-142242-152424-16422-3";
	const int	nbs[] = {
		-12,
		-249242,
		-142242,
		-152424,
		-16422,
		-3,
		0,
	};
	for (size_t i = 0; nbs[i]; ++i)
		ft_putnbr_fd((int)nbs[i], 1);
	cr_assert_stdout_eq_str(ref);
}

Test(ft_putnbr_fd, test_bounds, .init = cr_redirect_stdout)
{
	char		ref[100] = { 0, };
	const int	nbs[] = {
		INT_MIN,
		INT_MAX,
		0,
	};
	sprintf(ref, "%d%d", INT_MIN, INT_MAX);
	for (size_t i = 0; nbs[i]; ++i)
		ft_putnbr_fd((int)nbs[i], 1);
	cr_assert_stdout_eq_str(ref);
}
