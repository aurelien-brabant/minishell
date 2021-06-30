#include <criterion/criterion.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "libft.h"

TestSuite(ft_tolower);

Test(ft_tolower, test_basic)
{
	int	ref;
	int	ft;

	for (char c = 0; c < CHAR_MAX; c++)
	{
		ref = tolower(c);
		ft = ft_tolower(c);
		cr_assert(ref == ft, "For ascii %hhd:\nWas: %d\nExpected:%d", c, ft, ref);
	}
}
