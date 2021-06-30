#include <criterion/criterion.h>
#include <bsd/string.h>
#include "libft.h"

TestSuite(ft_strnstr);

Test(ft_strnstr, test_needle_present)
{
	const char	*haystack = "Hello world this is an haystack! I'am looking for a needle...";
	const char	*needle	= "needle";
	char	*ref = NULL;
	char	*ft = NULL;

	ref = strnstr(haystack, needle, 100); 
	ft = ft_strnstr(haystack, needle, 100);

	cr_assert(ref == ft, "For haystack=\"%s\"; needle=\"%s\":\nGot:\"%s\"\nWas:\"%s\"\n", haystack, needle, ref, ft);
}


Test(ft_strnstr, test_no_needle)
{
	const char	*haystack = "Hello world this is an haystack! I'am looking for a Needle...";
	const char	*needle	= "needle";
	char	*ref = NULL;
	char	*ft = NULL;

	ref = strnstr(haystack, needle, 100);
	ft = ft_strnstr(haystack, needle, 100);

	cr_assert(ref == ft, "For haystack=\"%s\"; needle=\"%s\":\nGot:\"%s\"\nWas:%s\n", haystack, needle, ref, ft);
}


/* Needle is partially matched, but len prevents scanning it entirely. */

Test(ft_strnstr, test_partial_needle_present)
{
	const char	*haystack = "Hello world thisno is an haystack! I'am looking for a Needle...";
	const char	*needle	= "no";
	char		*ref = NULL;
	char		*ft = NULL;

	ref = strnstr(haystack, needle, 17);
	ft = ft_strnstr(haystack, needle, 17);

	cr_assert(ref == ft, "For haystack=\"%s\"; needle=\"%s\":\nGot:\"%s\"\nWas:\"%s\"\n", haystack, needle, ref, ft);
}

Test(ft_strnstr, test_needle_at_very_end)
{
	const char	*haystack = "Hello world";
	const char	*needle	= "ld";
	char		*ref = NULL;
	char		*ft = NULL;

	ref = strnstr(haystack, needle, 15);
	ft = ft_strnstr(haystack, needle, 15);

	cr_assert(ref == ft, "For haystack=\"%s\"; needle=\"%s\":\nGot:\"%s\"\nWas:\"%s\"\n", haystack, needle, ref, ft);
}

Test(ft_strnstr, test_needle_at_very_start)
{
	const char	*haystack = "Hello world";
	const char	*needle	= "He";
	char		*ref = NULL;
	char		*ft = NULL;

	ref = strnstr(haystack, needle, 15);
	ft = ft_strnstr(haystack, needle, 15);

	cr_assert(ref == ft, "For haystack=\"%s\"; needle=\"%s\":\nGot:\"%s\"\nWas:\"%s\"\n", haystack, needle, ref, ft);
}

/* This should return a pointer to the beginning of the haystack */

Test(ft_strnstr, test_empty_needle)
{
	const char	*haystack = "Hello world";
	const char	*needle	= "\0";
	char		*ref = NULL;
	char		*ft = NULL;

	ref = strnstr(haystack, needle, 15);
	ft = ft_strnstr(haystack, needle, 15);

	cr_assert(ref == ft, "For haystack=\"%s\"; needle=\"%s\":\nGot:\"%s\"\nWas:\"%s\"\n", haystack, needle, ref, ft);
}

/* This should return NULL as zero characters are checked - this test
 * is here to test possible underflow of the len variable if done wrong.
*/

Test(ft_strnstr, test_zero_len)
{
	const char	*haystack = "Hello world";
	const char	*needle	= "\0";
	char		*ref = NULL;
	char		*ft = NULL;

	ref = strnstr(haystack, needle, 0);
	ft = ft_strnstr(haystack, needle, 0);

	cr_assert(ref == ft, "For haystack=\"%s\"; needle=\"%s\":\nGot:\"%s\"\nWas:\"%s\"\n", haystack, needle, ref, ft);
}
