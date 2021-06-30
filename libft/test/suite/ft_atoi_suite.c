#include <criterion/criterion.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_atoi);

Test(ft_atoi, test_positive)
{
	const char	*toparse = "54532";
	const int	ref = atoi(toparse);
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %d\n- Got: %d\n", toparse, ft, ref);
}

Test(ft_atoi, test_negative)
{
	const char	*toparse = "-54532";
	const int	ref = atoi(toparse);
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %d\n- Got: %d\n", toparse, ft, ref);
}

Test(ft_atoi, test_zero_value)
{
	const char	*toparse = "0";
	const int	ref = atoi(toparse);
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %d\n- Got: %d\n", toparse, ft, ref);
}

Test(ft_atoi, test_INT_MAX)
{
	const char	*toparse = "2147483647";
	const int	ref = atoi(toparse);
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %d\n- Got: %d\n", toparse, ft, ref);
}

Test(ft_atoi, test_INT_MIN)
{
	const char	*toparse = "-2147483648";
	const int	ref = atoi(toparse);
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %d\n- Got: %d\n", toparse, ft, ref);
}

Test(ft_atoi, test_overflow)
{
	const char	*toparse = "2147483648";
	const int	ref = INT_MAX;
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %d\n- Got: %d\n", toparse, ft, ref);
}

Test(ft_atoi, test_underflow)
{
	const char	*toparse = "-2147483649";
	const int	ref = INT_MIN;
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %d\n- Got: %d\n", toparse, ft, ref);
}

Test(ft_atoi, test_trailing_spaces)
{
	const char	*toparse = "\t\f   \v\t\t  -45     \n\r\r    ";
	const int	ref = atoi(toparse);
	const int	ft = ft_atoi(toparse);

	cr_assert(ref == ft, "For input: \"\\t\\f  \\v\\t\\t  -45     \\n\\r\\r    \":\n- Was: %d\n- Got: %d\n", ft, ref);
}
