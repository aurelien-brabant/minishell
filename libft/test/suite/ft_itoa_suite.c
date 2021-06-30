#include <criterion/criterion.h>
#include <string.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_itoa);

Test(ft_itoa, test_positive_value)
{
	char	*ref = "2436";
	char	out[1000];
	int		nb = 2436;
	char	*str = NULL;

	str = ft_itoa(nb);
	strcpy(out, str);
	free(str);
	cr_assert(strcmp(ref, out) == 0, "For integer input: %d\nGot: \"%s\"\nExpected:\"%s\"\n", nb, out, ref);
}

Test(ft_itoa, test_negative_value)
{
	char	*ref = "-2436";
	char	out[1000];
	int		nb = -2436;
	char	*str = NULL;

	str = ft_itoa(nb);
	strcpy(out, str);
	free(str);
	cr_assert(strcmp(ref, out) == 0, "For integer input: %d\nGot: \"%s\"\nExpected:\"%s\"\n", nb, out, ref);
}

Test(ft_itoa, test_INT_MIN)
{
	char	*ref = "-2147483648";
	char	out[1000];
	int		nb = INT_MIN;
	char	*str = NULL;

	str = ft_itoa(nb);
	strcpy(out, str);
	free(str);
	cr_assert(strcmp(ref, out) == 0, "For integer input: %d\nGot: \"%s\"\nExpected:\"%s\"\n", nb, out, ref);
}

Test(ft_itoa, test_INT_MAX)
{
	char	*ref = "2147483647";
	char	out[1000];
	int		nb = INT_MAX;
	char	*str = NULL;

	str = ft_itoa(nb);
	strcpy(out, str);
	free(str);
	cr_assert(strcmp(ref, out) == 0, "For integer input: %d\nGot: \"%s\"\nExpected:\"%s\"\n", nb, out, ref);
}

Test(ft_itoa, test_zero_value)
{
	char	*ref = "0";
	char	out[1000];
	int		nb = 0;
	char	*str = NULL;

	str = ft_itoa(nb);
	strcpy(out, str);
	free(str);
	cr_assert(strcmp(ref, out) == 0, "For integer input: %d\nGot: \"%s\"\nExpected:\"%s\"\n", nb, out, ref);
}
