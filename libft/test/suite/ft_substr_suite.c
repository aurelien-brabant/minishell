#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

TestSuite(ft_substr);

Test(ft_substr, test_basic)
{
	char	*ref = "hello world!";
	char	*exp = "lo wor";
	char	*substr;

	substr = ft_substr(ref, 3, 6);
	cr_expect(strcmp(substr, exp) == 0, "For s=\"%s\"; considering substr(s, 3, 6):\nWas:\"%s\"\nExpected:\"%s\"", ref, substr, exp);
	free(substr);
}

Test(ft_substr, test_oversized_len)
{
	char	*ref = "This is a test string, I love test strings";
	char	*exp = "s is a test string, I love test strings";
	char	*substr = 0;

	substr = ft_substr(ref, 3, 24992992);
	cr_expect(strcmp(substr, exp) == 0, "For s=\"%s\"; considering substr(s, 3, 24992992):\nWas:\"%s\"\nExpected:\"%s\"", ref, substr, exp);
	free(substr);
}

Test(ft_substr, test_zero_len)
{
	char	*ref = "This is a test string, I love test strings";
	char	*exp = "";
	char	*substr = 0;

	substr = ft_substr(ref, 3, 0);
	cr_expect(strcmp(substr, exp) == 0, "For s=\"%s\"; considering substr(s, 3, 24992992):\nWas:\"%s\"\nExpected:\"%s\"", ref, substr, exp);
	free(substr);
}

Test(ft_substr, test_from_start)
{
	char	*ref = "This is a test string, I love test strings";
	char	*exp = "This ";
	char	*substr = 0;

	substr = ft_substr(ref, 0, 5);
	cr_expect(strcmp(substr, exp) == 0, "For s=\"%s\"; considering substr(s, 0, 5):\nWas:\"%s\"\nExpected:\"%s\"", ref, substr, exp);
	free(substr);
}

Test(ft_substr, test_last_index)
{
	char	*ref = "last character is a Z";
	char	*exp = "Z";
	char	*substr = 0;

	substr = ft_substr(ref, 20, 1);
	cr_expect(strcmp(substr, exp) == 0, "For s=\"%s\"; considering substr(s, 20, 1):\nWas:\"%s\"\nExpected:\"%s\"", ref, substr, exp);
	free(substr);
}
