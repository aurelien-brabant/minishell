#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_realloc);

Test(ft_realloc, test_basic)
{
	char	*ref = "Hello worldHello world";
	char	*s = 0;

	s = strdup("Hello world");
	if (s == NULL)
		cr_assert_eq(0, 0, "Test ignored because of internal error");
	s = ft_realloc(s, strlen(s), strlen(s) * 2 + 1);
	//s = realloc(s, strlen(s) * 2 + 1);
	strcat(s, "Hello world");
	cr_expect(strcmp(s, ref) == 0, "Reallocation failed:\nWas:\"%s\"\nExpected:\"%s\"", s, ref);
	free(s);
}
