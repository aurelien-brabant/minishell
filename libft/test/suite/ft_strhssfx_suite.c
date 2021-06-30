#include <criterion/criterion.h>
#include <stdbool.h>
#include "libft.h"

TestSuite(ft_strhssfx);

Test(ft_strhssfx, test_basic)
{
	char	*ref = "main.c";
	char	*sfx = ".c";
	bool	exp = true;
	bool	ft = ft_strhssfx(ref, sfx);

	cr_assert(ft == exp, "For s=\"%s\"; suffix=\"%s\"\nWas:%d\nExpected: %d", ref, sfx, ft, exp);
}

Test(ft_strhssfx, test_case_sensitive)
{
	char	*ref = "hello helloworld how hel are you Hello hello hello";
	char	*sfx = "Hello";
	bool	exp = false;
	bool	ft = ft_strhssfx(ref, sfx);

	cr_assert(ft == exp, "For s=\"%s\"; suffix=\"%s\"\nWas:%d\nExpected: %d", ref, sfx, ft, exp);
}

Test(ft_strhssfx, test_no_suffix)
{
	char	*ref = "hello helloworld how hel are you Hello hello Hello";
	char	*sfx = "world";
	bool	exp = false;
	bool	ft = ft_strhssfx(ref, sfx);

	cr_assert(ft == exp, "For s=\"%s\"; suffix=\"%s\"\nWas:%d\nExpected: %d", ref, sfx, ft, exp);
}

Test(ft_strhssfx, test_str_equal)
{
	char	*ref = "main.c";
	char	*sfx = "main.c";
	bool	exp = true;
	bool	ft = ft_strhssfx(ref, sfx);

	cr_assert(ft == exp, "For s=\"%s\"; suffix=\"%s\"\nWas:%d\nExpected: %d", ref, sfx, ft, exp);
}
