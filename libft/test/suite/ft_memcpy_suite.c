#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_memcpy);

Test(ft_memcpy, test_basic)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem;
	void	*ftmem;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);
	refmem = memcpy(refbuf, "Hello world", 11);
	ftmem = ft_memcpy(ftbuf, "Hello world", 11);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf: \"%s\", considering memcpy(buf, \"érinté être\", 11):\nWas:\"%s\"\nExpected:\"%s\"", ref, ftbuf, refbuf);
	cr_assert(ftmem == ftbuf, "Your memcpy returned a different address than the one expected:\nWas:%p\nExpected:%p", ftmem, ftbuf);
}

Test(ft_memcpy, test_unsigned_cast)
{
	char	*ref = "XXXXXXXXXXXXXXXXXXX";
	char	refbuf[20] = { 0, };
	char	ftbuf[20] = { 0, };
	void	*refmem;
	void	*ftmem;

	strcpy(refbuf, ref);
	strcpy(ftbuf, ref);
	refmem = memcpy(refbuf, "érinté être", 17);
	ftmem = ft_memcpy(ftbuf, "érinté être", 17);

	cr_assert(memcmp(refbuf, ftbuf, 20) == 0, "For buf: \"%s\", considering memcpy(buf, \"érinté être\", 11):\nWas:\"%s\"\nExpected:\"%s\"", ref, ftbuf, refbuf);
	cr_assert(ftmem == ftbuf, "Your memcpy returned a different address than the one expected:\nWas:%p\nExpected:%p", ftmem, ftbuf);
}
