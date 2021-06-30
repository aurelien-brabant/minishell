#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strcasestr);

Test(ft_strcasestr, test_basic_diff_case)
{
	const char	*haystack = "Hello world this is an haystack! I'am looking for a NeeDle...";
	const char	*needle	= "neEdle";
	char	*ref;
	char	*ft;

	ref = strcasestr(haystack, needle); 
	ft = ft_strcasestr(haystack, needle);
}

/*

void	ft_strcasestr_simple_test(void)
{
	const char	*haystack = "Hello world this is an haystack! I'am looking for a NeeDle...";
	const char	*needle	= "neEdle";
	char	*ref;
	char	*ft;

	ref = (char *)haystack + 52; 
	ft = ft_strcasestr(haystack, needle);

	TEST_ASSERT_EQUAL_PTR(ref, ft);
}

void	ft_strcasestr_not_found(void)
{
	const char	*haystack = "Hello world this is an haystack! I'am looking for a Needly...";
	const char	*needle	= "needle";
	char	*ref;
	char	*ft;

	ref = NULL;
	ft = ft_strcasestr(haystack, needle);

	TEST_ASSERT_EQUAL_PTR(ref, ft);
}


void	ft_strcasestr_partial(void)
{
	const char	*haystack = "Hello world this is an haystack! I'am looking for a Needle...Nooho";
	const char	*needle	= "noohoh";
	char	*ref;
	char	*ft;

	ref = NULL;
	ft = ft_strcasestr(haystack, needle);

	TEST_ASSERT_EQUAL_PTR(ref, ft);
}

void	ft_strcasestr_end(void)
{
	const char	*haystack = "Hello worLD";
	const char	*needle	= "ld";
	char	*ref;
	char	*ft;

	ref = (char *)haystack + 9;
	ft = ft_strcasestr(haystack, needle);

	TEST_ASSERT_EQUAL_PTR(ref, ft);
}

void	ft_strcasestr_start(void)
{
	const char	*haystack = "HEllO world";
	const char	*needle	= "He";
	char	*ref;
	char	*ft;

	ref = (char *)haystack;
	ft = ft_strcasestr(haystack, needle);

	TEST_ASSERT_EQUAL_PTR(ref, ft);
}


void	ft_strcasestr_null_byte(void)
{
	const char	*haystack = "Hello world";
	const char	*needle	= "\0";
	char	*ref;
	char	*ft;

	ref = (char *)haystack;
	ft = ft_strcasestr(haystack, needle);

	TEST_ASSERT_EQUAL_PTR(ref, ft);
}
*/
