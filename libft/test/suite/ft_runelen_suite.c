#include <criterion/criterion.h>
#include "libft.h"

TestSuite(ft_runelen);

Test(ft_runelen, one_byte)
{
	t_rune	r = 0x007F;
	t_byte	ft = ft_runelen(r);
	t_byte	exp = 1;

	cr_assert(ft == exp, "For rune=%u:\nWas: %hhd\nExpected: %hhd", r, ft, exp);
}

Test(ft_runelen, two_bytes)
{
	t_rune	r = 0x07FF;
	t_byte	ft = ft_runelen(r);
	t_byte	exp = 2;

	cr_assert(ft == exp, "For rune=%u:\nWas: %hhd\nExpected: %hhd", r, ft, exp);
}

Test(ft_runelen, three_bytes)
{
	t_rune	r = 0xFFFF;
	t_byte	ft = ft_runelen(r);
	t_byte	exp = 3;

	cr_assert(ft == exp, "For rune=%u:\nWas: %hhd\nExpected: %hhd", r, ft, exp);
}

Test(ft_runelen, four_bytes)
{
	t_rune	r = 0x10FFFF;
	t_byte	ft = ft_runelen(r);
	t_byte	exp = 4;

	cr_assert(ft == exp, "For rune=%u:\nWas: %hhd\nExpected: %hhd", r, ft, exp);
}
