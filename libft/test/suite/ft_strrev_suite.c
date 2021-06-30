#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strrev);

Test(ft_strrev, test_odd_len)
{
	char	*base = "My name is abrabant";	
	char	*ref = "tnabarba si eman yM";
	char	revbuf[100];

	strcpy(revbuf, base);
	ft_strrev(revbuf);
	cr_assert(strcmp(ref, revbuf) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", base, revbuf, ref);
}

Test(ft_strrev, test_even_len)
{
	char	*base = "My name is abrabant!";	
	char	*ref = "!tnabarba si eman yM";
	char	revbuf[100];

	strcpy(revbuf, base);
	ft_strrev(revbuf);
	cr_assert(strcmp(ref, revbuf) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", base, revbuf, ref);
}
