#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strchri);

Test(ft_strchri, test_char_present)
{
	const char	*ref = "Hahwdjeawwaapekw[qpwrkawl/%weowr//";
	const int	refrt = 1; 
	const char	c = 'a';
	int			ftrt = 0;

	ftrt = ft_strchri(ref, c);

	cr_assert(refrt == ftrt, "For s=\"%s\"; c='%c':Was:\"%d\"\nExpected:\"%d\"", ref, c, ftrt, refrt);
}

Test(ft_strchri, test_char_not_present)
{
	const char	*ref = "Hahwdjeawwaapekw[qpwrkawl/%weowr//";
	const int	refrt = -1; 
	const char	c = '-';
	int			ftrt = 0;

	ftrt = ft_strchri(ref, c);

	cr_assert(refrt == ftrt, "For s=\"%s\"; c='%c':Was:\"%d\"\nExpected:\"%d\"", ref, c, ftrt, refrt);
}
