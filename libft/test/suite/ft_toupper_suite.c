#include <criterion/criterion.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "libft.h"

TestSuite(ft_toupper);

Test(ft_toupper, test_basic)
{
	int	ref;
	int	ft;

	for (char c = 0; c < CHAR_MAX; c++)
	{
		ref = toupper(c);
		ft = ft_toupper(c);
		cr_assert(ref == ft, "For ascii %hhd:\nWas: %d\nExpected:%d", c, ft, ref);
	}
}
