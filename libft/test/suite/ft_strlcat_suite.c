#include <criterion/criterion.h>
#include <bsd/string.h>
#include "libft.h"

TestSuite(ft_strlcat);

Test(ft_strlcat, test_full_cat)
{
	char			ftdest[100] = "hello ";
	char			refdest[100] = "hello ";
	const char		*str = "world";
	const size_t	len = strlen(ftdest) + strlen(str) + 1;
	size_t			ftrt;
	size_t			refrt;

	refrt = strlcat(refdest, str, len);
	ftrt = ft_strlcat(ftdest, str, len);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\"; dst=\"%s\"; len=%ld:\nWas:\"%s\"\nExpected:\"%s\"", str, "hello ", len, ftdest, refdest);
	cr_assert(refrt == ftrt, "Concatenation done successfully, but return values differ:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}

Test(ft_strlcat, test_do_not_concat_due_to_dest_length)
{
	char			ftdest[100] = "hello ";
	char			refdest[100] = "hello ";
	const char		*str = "world";
	const size_t	len = 3;
	size_t			ftrt;
	size_t			refrt;

	refrt = strlcat(refdest, str, len);
	ftrt = ft_strlcat(ftdest, str, len);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\"; dst=\"%s\"; len=%ld:\nWas:\"%s\"\nExpected:\"%s\"", str, "hello ", len, ftdest, refdest);
	cr_assert(refrt == ftrt, "Concatenation done successfully, but return values differ:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}

Test(ft_strlcat, test_partial_concat)
{
	char			ftdest[100] = "hello ";
	char			refdest[100] = "hello ";
	const char		*str = "world";
	const size_t	len = strlen(ftdest) + 4;
	size_t			ftrt;
	size_t			refrt;

	refrt = strlcat(refdest, str, len);
	ftrt = ft_strlcat(ftdest, str, len);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\"; dst=\"%s\"; len=%ld:\nWas:\"%s\"\nExpected:\"%s\"", str, "hello ", len, ftdest, refdest);
	cr_assert(refrt == ftrt, "Concatenation done successfully, but return values differ:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}

Test(ft_strlcat, test_concat_dst_size)
{
	char			ftdest[100] = "hello ";
	char			refdest[100] = "hello ";
	const char		*str = "world";
	const size_t	len = strlen(ftdest);
	size_t			ftrt;
	size_t			refrt;

	refrt = strlcat(refdest, str, len);
	ftrt = ft_strlcat(ftdest, str, len);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\"; dst=\"%s\"; len=%ld:\nWas:\"%s\"\nExpected:\"%s\"", str, "hello ", len, ftdest, refdest);
	cr_assert(refrt == ftrt, "Concatenation done successfully, but return values differ:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}
