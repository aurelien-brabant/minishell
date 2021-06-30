#include <criterion/criterion.h>
#include <signal.h>
#include "libft.h"

TestSuite(ft_strcmpset);

Test(ft_strcmpset, test_eq)
{
	const char	*s1 = "--option=\"random string\"";
	const char	*s2 = "--option";
	const char	*set = "=";
	const int	expected = 0;

	cr_expect_eq(ft_strcmpset(s1, s2, set), expected);
}

Test(ft_strcmpset, test_only_set)
{
	const char	*s1 = "=";
	const char	*s2 = "=";
	const char	*set = "=";
	const int	expected = 0;

	cr_expect_eq(ft_strcmpset(s1, s2, set), expected);
}
