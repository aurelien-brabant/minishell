#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_memset);

Test(ft_memset, test_basic)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[21] = { 0, };
	char	ftbuf[21] = { 0, };
	void	*refmem;
	void	*ftmem;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memset(refbuf, 'A', 10);
	ftmem = ft_memset(ftbuf, 'A', 10);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf: \"%s\", considering memset(buf, 'A', 10):\nWas:\"%s\"\nExpected:\"%s\"", ref, ftbuf, refbuf);
	cr_assert(ftmem == ftbuf, "Your memset returned a different address than the one expected:\nWas:%p\nExpected:%p", ftmem, ftbuf);
}

/* memset should cast every character as unsigned char before or while setting the bytes */

Test(ft_memset, test_unsigned_cast)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXXX";
	char	refbuf[21] = { 0, };
	char	ftbuf[21] = { 0, };
	void	*refmem;
	void	*ftmem;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);

	refmem = memset(refbuf, 222, 15);
	ftmem = ft_memset(ftbuf, 222, 15);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf: \"%s\", considering memset(buf, 222, 15):\nWas:\"%s\"\nExpected:\"%s\"", ref, ftbuf, refbuf);
	cr_assert(ftmem == ftbuf, "Your memset returned a different address than the one expected:\nWas:%p\nExpected:%p", ftmem, ftbuf);
}
