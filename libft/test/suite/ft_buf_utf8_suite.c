#include <criterion/criterion.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

TestSuite(ft_buf_utf8);

Test(ft_buf_utf8, one_byte)
{
	char	ref[5];
	t_byte	dst[5];
	t_byte	*ptr;

	setlocale(LC_ALL, "");
	sprintf(ref, "%lc", (wint_t)0x78);
	ptr = ft_buf_utf8(dst, 0x78);
	cr_assert(memcmp(ref, dst, 1) == 0, "Rune badly encoded:\nWas:\"%s\"\nExpected:\"%s\"", dst, ref);
	cr_assert(dst == ptr, "Encoding done correctly, but bad return value:\nWas: %p\nExpected: %p", ptr, dst);
}

Test(ft_buf_utf8, two_bytes)
{
	char	ref[5];
	t_byte	dst[5];
	t_byte	*ptr;

	setlocale(LC_ALL, "");
	sprintf(ref, "%lc", (wint_t)0x0788);
	ptr = ft_buf_utf8(dst, 0x788);
	cr_assert(memcmp(ref, dst, 2) == 0, "Rune badly encoded:\nWas:\"%s\"\nExpected:\"%s\"", dst, ref);
	cr_assert(dst == ptr, "Encoding done correctly, but bad return value:\nWas: %p\nExpected: %p", ptr, dst);
}

Test(ft_buf_utf8, three_bytes)
{
	char	ref[5];
	t_byte	dst[5];
	t_byte	*ptr;

	setlocale(LC_ALL, "");
	sprintf(ref, "%lc", (wint_t)0x0945);
	ptr = ft_buf_utf8(dst, 0x0945);
	cr_assert(memcmp(ref, dst, 3) == 0, "Rune badly encoded:\nWas:\"%s\"\nExpected:\"%s\"", dst, ref);
	cr_assert(dst == ptr, "Encoding done correctly, but bad return value:\nWas: %p\nExpected: %p", ptr, dst);
}

Test(ft_buf_utf8, four_bytes)
{
	char	ref[5];
	t_byte	dst[5];
	t_byte	*ptr;

	setlocale(LC_ALL, "");
	sprintf(ref, "%lc", (wint_t)0x12000);
	ptr = ft_buf_utf8(dst, 0x12000);
	cr_assert(memcmp(ref, dst, 4) == 0, "Rune badly encoded:\nWas:\"%s\"\nExpected:\"%s\"", dst, ref);
	cr_assert(dst == ptr, "Encoding done correctly, but bad return value:\nWas: %p\nExpected: %p", ptr, dst);
}
