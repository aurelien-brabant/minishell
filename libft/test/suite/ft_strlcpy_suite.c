#include <criterion/criterion.h>
#include <bsd/string.h>
#include "libft.h"

TestSuite(ft_strlcpy);

Test(ft_strlcpy, test_basic_limited_len)
{
	char			ftdest[100];
	char			refdest[100];
	const char		*src = "Hello world";
	size_t			ftrt;
	size_t			refrt;
	
	refrt = strlcpy(refdest, src, 5);
	ftrt = ft_strlcpy(ftdest, src, 5);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\" and len=%d:\nWas: \"%s\"\nExpected: \"%s\"", src, 5, ftdest, refdest);
	cr_assert(refrt == ftrt, "Copy was done correctly, but return values differs:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}

Test(ft_strlcpy, test_basic_zero_len)
{
	char			ftdest[100] = "I was here before copy!";
	char			refdest[100] = "I was here before copy!";
	const char		*src = "Hello world";
	size_t			ftrt;
	size_t			refrt;
	
	refrt = strlcpy(refdest, src, 0);
	ftrt = ft_strlcpy(ftdest, src, 0);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\" and len=%d:\nWas: \"%s\"\nExpected: \"%s\"", src, 0, ftdest, refdest);
	cr_assert(refrt == ftrt, "Copy was done correctly, but return values differs:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}

Test(ft_strlcpy, test_len_greater_than_strlen_plus_one)
{
	char			ftdest[100] = "I was here before copy!";
	char			refdest[100] = "I was here before copy!";
	const char		*src = "Hello world";
	size_t			ftrt;
	size_t			refrt;
	
	refrt = strlcpy(refdest, src, 45);
	ftrt = ft_strlcpy(ftdest, src, 45);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\" and len=%d:\nWas: \"%s\"\nExpected: \"%s\"", src, 45, ftdest, refdest);
	cr_assert(refrt == ftrt, "Copy was done correctly, but return values differs:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}

Test(ft_strlcpy, test_len_equal_to_strlen)
{
	char			ftdest[100] = "I was here before copy!";
	char			refdest[100] = "I was here before copy!";
	const char		*src = "Hello world";
	const size_t	len = strlen(src);
	size_t			ftrt;
	size_t			refrt;
	
	refrt = strlcpy(refdest, src, len);
	ftrt = ft_strlcpy(ftdest, src, len);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\" and len=%ld:\nWas: \"%s\"\nExpected: \"%s\"", src, strlen(src), ftdest, refdest);
	cr_assert(refrt == ftrt, "Copy was done correctly, but return values differs:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}

Test(ft_strlcpy, test_len_equal_to_strlen_plus_one)
{
	char				ftdest[100] = "I was here before copy!";
	char				refdest[100] = "I was here before copy!";
	const char			*src = "Hello world";
	const size_t len	= strlen(src);
	size_t				ftrt;
	size_t				refrt;
	
	refrt = strlcpy(refdest, src, len + 1);
	ftrt = ft_strlcpy(ftdest, src, len + 1);

	cr_assert(strcmp(ftdest, refdest) == 0, "For src=\"%s\" and len=%ld:\nWas: \"%s\"\nExpected: \"%s\"", src, strlen(src) + 1, ftdest, refdest);
	cr_assert(refrt == ftrt, "Copy was done correctly, but return values differs:\nWas: %ld\nExpected: %ld", ftrt, refrt);
}
