#include <criterion/criterion.h>
#include <ctype.h>
#include "libft.h"

TestSuite(ft_isalpha);

Test(ft_isalpha, test_all_ascii_chars)
{
	int	ft = 0;
	int	ref = 0;

	for (int c = 0; c <= 127; ++c)
	{
		ref = ft_isalpha(c);
		ft = ft_isalpha(c);
		cr_assert(ref ? ft > 0 : !ft, "For ascii %d:\nWas: %d\nExpected: %d\nWARNING: Your result needs to be zero or non-zero. There's no need to replicate the exact return value, as it is UNDEFINED!", c, ft, ref);
	}
}
