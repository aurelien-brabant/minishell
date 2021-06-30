#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strrchr);

Test(ft_strrchr, test_char_present)
{
	char	*ref = "Hello world Hello boy Hello dude!";
	char	*rf = strrchr(ref, 'H');
	char	*ft = ft_strrchr(ref, 'H');

	cr_assert(rf == ft, "For s=\"%s\"; c='%c'\nWas:\"%s\"\nExpected:\"%s\"", ref, 'H', ft, rf);
}

Test(ft_strrchr, test_char_not_present)
{
	char	*ref = "Hello world Hello boy Hello dude!";
	char	*rf = strrchr(ref, 'X');
	char	*ft = ft_strrchr(ref, 'X');

	cr_assert(rf == ft, "For s=\"%s\"; c='%c'\nWas:\"%s\"\nExpected:\"%s\"", ref, 'X', ft, rf);
}

Test(ft_strrchr, test_null_byte)
{
	char	*ref = "Hello world Hello boy Hello dude!";
	char	*rf = strrchr(ref, 0);
	char	*ft = ft_strrchr(ref, 0);

	cr_assert(rf == ft, "For s=\"%s\"; c='%c'\nWas:\"%s\"\nExpected:\"%s\"", ref, 0, ft, rf);
}
