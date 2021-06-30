#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strjoin);

Test(ft_strjoin, test_basic)
{
	char	ftbuf[100] = { 0 };
	char	refbuf[100] = { 0 };
	char	*s1 = "String 1";
	char	*s2 = "String 2";
	char	*joined = NULL;

	joined = ft_strjoin(s1, s2);
	strcpy(ftbuf, joined);
	free(joined);
	strcat(refbuf, s1);
	strcat(refbuf, s2);

	cr_assert(strcmp(ftbuf, refbuf) == 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", s1, s2, ftbuf, refbuf);
}

Test(ft_strjoin, test_join_empty)
{
	char	ftbuf[100] = { 0 };
	char	refbuf[100] = { 0 };
	char	*s1 = "";
	char	*s2 = "";
	char	*joined = NULL;

	joined = ft_strjoin(s1, s2);
	strcpy(ftbuf, joined);
	free(joined);
	strcat(refbuf, s1);
	strcat(refbuf, s2);

	cr_assert(strcmp(ftbuf, refbuf) == 0, "For s1=\"%s\"; s2=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", s1, s2, ftbuf, refbuf);
}
