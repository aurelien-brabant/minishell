#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strchr);

Test(ft_strchr, test_basic)
{
	char	*ref = "Hello world Hello boy Hello dude!";
	char	*rf = strchr(ref, 'H');
	char	*ft = ft_strchr(ref, 'H');

	cr_assert(rf == ft, "For s=\"%s\"; c='%c':\nWas: \"%s\"\nExpected:\"%s\"", ref, 'H', ft, rf);
}

Test(ft_strchr, test_nochar)
{
	char	*ref = "Hello world Hello boy Hello dude!";
	char	*rf = strchr(ref, 'X');
	char	*ft = ft_strchr(ref, 'X');

	cr_assert(rf == ft, "For s=\"%s\"; c='%c':\nWas: \"%s\"\nExpected:\"%s\"", ref, 'X', ft, rf);
}

Test(ft_strchr, test_null_byte)
{
	char	*ref = "Hello world Hello boy Hello dude!";
	char	*rf = strchr(ref, 0);
	char	*ft = ft_strchr(ref, 0);

	cr_assert(rf == ft, "For s=\"%s\"; c='%c':\nWas: \"%s\"\nExpected:\"%s\"", ref, 'X', ft, rf);
}
