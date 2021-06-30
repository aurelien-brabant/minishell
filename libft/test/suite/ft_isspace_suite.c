#include <criterion/criterion.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_isspace);

Test(ft_isspace, test_basic)
{
	int	ftrt = 0;
	int rfrt;

	for (char i = 0; i < CHAR_MAX; i++)
	{
		ftrt = ft_isspace(i);
		if ((rfrt = isspace(i)))
			cr_assert(ftrt > 0, "For ascii %d:\nWas: %d\nExpected: %d", i, ftrt, rfrt);
		else
			cr_assert(ftrt == 0, "For ascii %d:\nWas: %d\nExpected: %d", i, ftrt, rfrt);
	}
}
