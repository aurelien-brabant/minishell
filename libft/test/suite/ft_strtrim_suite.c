#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strtrim);

Test(ft_strtrim, test_basic)
{
	char	*ref = "Hello world";
	char	ftbuf[1000];
	char	*totrim = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeHello worldeeeeeeekkek";
	char	*set = "ek";
	char	*trimed = NULL;

	trimed = ft_strtrim(totrim, set);
	strcpy(ftbuf, trimed);
	free(trimed);

	cr_assert(strcmp(ftbuf, ref) == 0, "For buf=\"%s\"; set=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", totrim, set, ftbuf, ref);
}

Test(ft_strtrim, test_empty_set)
{
	char	*ref = "Hello world";
	char	ftbuf[1000];
	char	*totrim = "Hello world";
	char	*set = "";
	char	*trimed = NULL;

	trimed = ft_strtrim(totrim, set);
	strcpy(ftbuf, trimed);
	free(trimed);

	cr_assert(strcmp(ftbuf, ref) == 0, "For buf=\"%s\"; set=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", totrim, set, ftbuf, ref);
}

Test(ft_strtrim, test_big_trim)
{
	char	*ref = "bb   Hello    world       how are you";
	char	ftbuf[1000];
	char	*totrim = "    aa     a   a a    aa a  a   a a  a  x x x  x  x   bb   Hello    world       how are you                               a aaa                   a  a a axx";
	char	*set = "ax ";
	char	*trimed = NULL;

	trimed = ft_strtrim(totrim, set);
	strcpy(ftbuf, trimed);
	free(trimed);

	cr_assert(strcmp(ftbuf, ref) == 0, "For buf=\"%s\"; set=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", totrim, set, ftbuf, ref);
}
