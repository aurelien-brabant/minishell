#include <criterion/criterion.h>
#include <ctype.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_isascii);

Test(ft_isascii, test_from_minus_one_to_CHAR_MAX)
{
	int	ref = 0;
	int ft = 0;

	for (int c = -1; c <= UCHAR_MAX; ++c)
	{
		ref = isascii(c);
		ft = isascii(c);
		cr_assert(ref ? ft > 0 : !ft, "For char %d:\nWas: %d\nExpected: %d\nWARNING: Your result needs to be zero or non-zero. There's no need to replicate the exact return value, as it is UNDEFINED!", c, ft, ref);
	}
}
