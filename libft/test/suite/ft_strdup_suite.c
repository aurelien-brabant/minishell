#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strdup);

Test(ft_strdup, test_basic)
{
	char	*ref = "Hello world";
	char	*dup;

	dup = ft_strdup(ref);
	//Will produce a crash if duped memory is not readable.
	dup[0] = dup[0];
	cr_expect(strcmp(ref, dup) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, dup, ref);
	free(dup);
}

Test(ft_strdup, test_empty_string)
{
	char	*ref = "";
	char	*dup;

	dup = ft_strdup(ref);
	//Will produce a crash if duped memory is not readable.
	dup[0] = dup[0];
	cr_expect(strcmp(ref, dup) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, dup, ref);
	free(dup);
}
