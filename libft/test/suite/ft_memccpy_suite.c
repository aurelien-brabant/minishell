#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_memccpy);

Test(ft_memccpy, test_char_present)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem = 0;
	void	*ftmem = 0;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memccpy(refbuf, "Hello| world", '|', 11);
	ftmem = ft_memccpy(ftbuf, "Hello| world", '|', 11);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf=\"%s\", considering memccpy(buf, \"Hello| world\", '|', 11):\nWas: %s\nExpected: %s", ref, ftbuf, refbuf);

	//Checking that the character at the address before is the searched one.
	cr_assert(((char *)ftmem)[-1], "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}

Test(ft_memccpy, test_char_after_len)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem = 0;
	void	*ftmem = 0;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memccpy(refbuf, "Hello| world", '|', 5);
	ftmem = ft_memccpy(ftbuf, "Hello| world", '|', 5);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf=\"%s\", considering memccpy(buf, \"Hello| world\", '|', 5):\nWas: %s\nExpected: %s", ref, ftbuf, refbuf);

	//checking that NULL has been returned as c has not been found in the 5 first bytes.
	cr_assert(!ftmem, "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}

Test(ft_memccpy, test_char_at_last_index)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem = 0;
	void	*ftmem = 0;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memccpy(refbuf, "Hello| world", '|', 6);
	ftmem = ft_memccpy(ftbuf, "Hello| world", '|', 6);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf=\"%s\", considering memccpy(buf, \"Hello| world\", '|', 6):\nWas: %s\nExpected: %s", ref, ftbuf, refbuf);

	cr_assert(((char *)ftmem)[-1] == '|', "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}

Test(ft_memccpy, test_zero_len)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem = 0;
	void	*ftmem = 0;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memccpy(refbuf, "Hello| world", '|', 0);
	ftmem = ft_memccpy(ftbuf, "Hello| world", '|', 0);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf=\"%s\", considering memccpy(buf, \"Hello| world\", '|', 0):\nWas: %s\nExpected: %s", ref, ftbuf, refbuf);

	//checking that NULL has been returned as c has not been found in the 5 first bytes.
	cr_assert(!ftmem, "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}

Test(ft_memccpy, test_unsigned_cast)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem = 0;
	void	*ftmem = 0;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memccpy(refbuf, "Héllo wôrld", '|', 13);
	ftmem = ft_memccpy(ftbuf, "Héllo wôrld", '|', 13);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf=\"%s\", considering memccpy(buf, \"Héllo wôrld\", '|', 13):\nWas: %s\nExpected: %s", ref, ftbuf, refbuf);

	//checking that NULL has been returned as c has not been found in the 5 first bytes.
	cr_assert(!ftmem, "You copied the bytes correctly, but you didn't return the right address:\nWas: %p\nExpected: %p", ftmem, refmem);
}
