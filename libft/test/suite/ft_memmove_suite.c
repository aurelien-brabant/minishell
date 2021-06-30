#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_memmove);

Test(ft_memmove, test_basic)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem;
	void	*ftmem;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memmove(refbuf, "Hello world", 10);
	ftmem = ft_memmove(ftbuf, "Hello world", 10);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf=\"%s\", considering memmove(refbuf, \"Hello world\", 10):\nWas:%s\nExpected:%s", ref, ftbuf, refbuf);
	cr_assert(ftmem == ftbuf, "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}

Test(ft_memmove, test_unsigned_cast)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem;
	void	*ftmem;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memmove(refbuf, "Héllo wôrld", 10);
	ftmem = ft_memmove(ftbuf, "Héllo wôrld", 10);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf=\"%s\", considering memmove(refbuf, \"Héllo wôrld\", 10):\nWas:%s\nExpected:%s", ref, ftbuf, refbuf);
	cr_assert(ftmem == ftbuf, "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}

Test(ft_memmove, test_overlap)
{
	char	refbuf[50] = "Hello world, I hope this will not overlap badly.";
	char	ftbuf[50] = "Hello world, I hope this will not overlap badly.";
	void	*refmem = 0;
	void	*ftmem = 0;
	char	*ref;

	ref = ft_strdup(refbuf);

	refmem = memmove(&refbuf[10], refbuf, 39);
	ftmem = ft_memmove(&ftbuf[10], ftbuf, 39);

	cr_assert(memcmp(refbuf, ftbuf, 50) == 0, "For buf=\"%s\", considering memmove(buf, \"Hello world, I hope this will not overlap badly.\", 39):\nWas:\"%s\"\nExpected:\"%s\"", ref, ftbuf, refbuf);
	cr_assert(ftmem == &ftbuf[10], "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}

Test(ft_memmove, test_unsigned_overlap)
{
	char	refbuf[50] = "Bjr monde, j'espère que t'as pas oublié le cast.";
	char	ftbuf[50] = "Bjr monde, j'espère que t'as pas oublié le cast.";
	void	*refmem = 0;
	void	*ftmem = 0;
	char	*ref;

	ref = ft_strdup(refbuf);

	refmem = memmove(&refbuf[10], refbuf, 39);
	ftmem = ft_memmove(&ftbuf[10], ftbuf, 39);

	cr_assert(memcmp(refbuf, ftbuf, 50) == 0, "For buf=\"%s\", considering memmove(buf, \"Hello world, I hope this will not overlap badly.\", 39):\nWas:\"%s\"\nExpected:\"%s\"", ref, ftbuf, refbuf);
	cr_assert(ftmem == &ftbuf[10], "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}
