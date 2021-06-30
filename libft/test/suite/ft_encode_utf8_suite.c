#include <criterion/criterion.h>
#include <locale.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "libft.h"

TestSuite(ft_encode_utf8);

Test(ft_encode_utf8, test_encoding)
{
	char	refbuf[100];
	t_rune	r[] = { 0x20, 0x45, 0x3041, 0x3042, 0x3043, 0x3044, 0xFF77, 0xFF7, 0x40, 0x11000, 0x84F, 0x300, 0x45E, 0x45FF, 0x0 };
	t_byte	*encoded = NULL;

	setlocale(LC_ALL, "");
	sprintf(refbuf, "%ls", (wchar_t *)r);
	encoded = ft_encode_utf8(r);
	cr_assert(strcmp((char *)encoded, refbuf) == 0, "Bad encoding.\nWas:\"%s\"\nExpected:\"%s\"", encoded, refbuf);
}
