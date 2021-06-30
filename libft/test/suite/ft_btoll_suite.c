#include <criterion/criterion.h>
#include <stdio.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_btoll);

/* BASE 10 */

Test(ft_btoll, test_positive_bten)
{
	const char	*toparse = "54532";
	const long long ref = 54532; 
	const long long ft = ft_btoll(toparse, 10);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_negative_bten)
{
	const char	*toparse = "-54532";
	const long long ref = -54532;
	const long long ft = ft_btoll(toparse, 10);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_zero_value_bten)
{
	const char	*toparse = "0";
	const long long ref = 0;
	const long long ft = ft_btoll(toparse, 10);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

/* BASE 16 */

Test(ft_btoll, test_positive_bhexa)
{
	const char	*toparse = "D504";
	const long long ref = 0xD504; 
	const long long ft = ft_btoll(toparse, 16);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_negative_bhexa)
{
	const char	*toparse = "-D504";
	const long long ref = -0xD504;
	const long long ft = ft_btoll(toparse, 16);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_zero_value_bhexa)
{
	const char	*toparse = "0";
	const long long ref = 0;
	const long long ft = ft_btoll(toparse, 16);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

/* BASE 8 */

Test(ft_btoll, test_positive_boct)
{
	const char	*toparse = "152404";
	const long long ref = 0152404; 
	const long long ft = ft_btoll(toparse, 8);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_negative_boct)
{
	const char	*toparse = "-152404";
	const long long ref = -0152404;
	const long long ft = ft_btoll(toparse, 8);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_zero_value_boct)
{
	const char	*toparse = "0";
	const long long ref = 0;
	const long long ft = ft_btoll(toparse, 8);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

/* BASE 2 */

Test(ft_btoll, test_positive_bbin)
{
	const char	*toparse = "1110";
	const long long ref = 14; 
	const long long ft = ft_btoll(toparse, 2);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_negative_bbin)
{
	const char	*toparse = "-1110";
	const long long ref = -14;
	const long long ft = ft_btoll(toparse, 2);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_zero_value_bbin)
{
	const char	*toparse = "0";
	const long long ref = 0;
	const long long ft = ft_btoll(toparse, 2);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

/*
** Test the boundaries of a long long long longword
*/

Test(ft_btoll, test_llong_max_bhex)
{
	char			toparse[100];
	const long long	ref = LLONG_MAX;

	sprintf(toparse, "%llx", LLONG_MAX);

	const long long	ft = ft_btoll(toparse, 16);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}

Test(ft_btoll, test_llong_min_boct)
{
	char			toparse[100];
	const long long	ref = LLONG_MIN;

	sprintf(toparse, "%llo", LLONG_MIN);

	const long long	ft = ft_btoll(toparse, 8);

	cr_assert(ref == ft, "For input \"%s\":\n- Was: %lld\n- Got: %lld\n", toparse, ft, ref);
}
