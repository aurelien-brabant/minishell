#include <criterion/criterion.h>
#include <stdbool.h>
#include "libft.h"

TestSuite(ft_strhsprfx);

Test(ft_strhsprfx, test_prefix_present)
{
	char	*ref = "Hello helloworld how hel are you Hello hello Hello";
	char	*prfx = "Hello";
	bool	exp = true;
	bool	ft = ft_strhsprfx(ref, prfx);

	cr_assert(ft == exp, "For s=\"%s\"; prefix=\"%s\"\nWas:%d\nExpected: %d", ref, prfx, ft, exp);
}

Test(ft_strhsprfx, test_case_sensitive)
{
	char	*ref = "hello helloworld how hel are you Hello hello Hello";
	char	*prfx = "Hello";
	bool	exp = false;
	bool	ft = ft_strhsprfx(ref, prfx);

	cr_assert(ft == exp, "For s=\"%s\"; prefix=\"%s\"\nWas:%d\nExpected: %d", ref, prfx, ft, exp);
}

Test(ft_strhsprfx, test_no_prefix)
{
	char	*ref = "hello helloworld how hel are you Hello hello Hello";
	char	*prfx = "ello";
	bool	exp = false;
	bool	ft = ft_strhsprfx(ref, prfx);

	cr_assert(ft == exp, "For s=\"%s\"; prefix=\"%s\"\nWas:%d\nExpected: %d", ref, prfx, ft, exp);
}

Test(ft_strhsprfx, test_str_equal)
{
	char	*ref = "main.c";
	char	*sfx = "main.c";
	bool	exp = true;
	bool	ft = ft_strhsprfx(ref, sfx);

	cr_assert(ft == exp, "For s=\"%s\"; prefix=\"%s\"\nWas:%d\nExpected: %d", ref, sfx, ft, exp);
}
