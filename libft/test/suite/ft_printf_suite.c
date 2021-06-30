#include <criterion/criterion.h>
#include <stdio.h>
#include "libft.h"
#include <limits.h>
#define MAX_BUF 1000

TestSuite(ft_printf);

/*
** As all the printf functions are sharing the same codebase, not all of them
** have a seperated test suite (for ease). Only the ft_sprintf function is
** used for tests, because the conversion stuff is handled by the same code
** in all the printf functions. Output method changes, argument list too, but
** the changes are minor and do not justify special test suites. Some tests
** may be added here if problems with some special printf functions are
** encountered while using them.
*/

Test(ft_printf, test_string_without_format)
{
	const char	*fmt = "Hello this is a simple line\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt);
	sprintf(refbuf, fmt);

	cr_expect_str_eq(ftbuf, refbuf);
}

/*
** Unlike the subject tells us to do, the % specifier doesn't support
** a width. This is undefined behaviour.
*/

Test(ft_printf, test_s_conv)
{
	const char	*fmt = "%% %% %% %%%%%% %%%% %%%%      %%%% %%  %%\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt);
	sprintf(refbuf, fmt);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_percent_conv)
{
	const char	*strings[] = {
		"Hello",
		"How",
		"Are",
		"You",
	};
	const char	*fmt = "1:%s 2:%s 3:%s 4:%s";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, strings[0], strings[1], strings[2], strings[3]);
	sprintf(refbuf, fmt, strings[0], strings[1], strings[2], strings[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_c_conv)
{
	const char	chars[] = {
		'a',
		'%',
		'c',
		0,
	};
	const char	*fmt = "1:%c 2:%c 3:%c 4:%c";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, chars[0], chars[1], chars[2], chars[3]);
	sprintf(refbuf, fmt, chars[0], chars[1], chars[2], chars[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_d_conv)
{
	const int	nbs[] = {
		INT_MAX,
		0,
		INT_MIN,
		42,
	};
	const char	*fmt = "1:%d 2:%d 3:%d 4:%d";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);
	sprintf(refbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_x_conv)
{
	const int	nbs[] = {
		INT_MAX,
		0,
		INT_MIN,
		42,
	};
	const char	*fmt = "1:%x 2:%x 3:%x 4:%x";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);
	sprintf(refbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_X_conv)
{
	const int	nbs[] = {
		INT_MAX,
		0,
		INT_MIN,
		42,
	};
	const char	*fmt = "1:%X 2:%X 3:%X 4:%X";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);
	sprintf(refbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_u_conv)
{
	const unsigned int	nbs[] = {
		UINT_MAX,
		0,
		42,
		23200,
	};
	const char	*fmt = "1:%u 2:%u 3:%u 4:%u";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);
	sprintf(refbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_p_conv)
{
	const unsigned int	nbs[] = {
		UINT_MAX,
		0,
		42,
		23200,
	};
	const char	*fmt = "1:%p 2:%p 3:%p 4:%p";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, &nbs[0], &nbs[1], &nbs[2], &nbs[3]);
	sprintf(refbuf, fmt, &nbs[0], &nbs[1], &nbs[2], &nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_flag_1)
{
	const char	*fmt = "hey %#x %#X %+d % d nice\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, 42, 42, 42, 42);
	sprintf(refbuf, fmt, 42, 42, 42, 42);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_flag_only)
{
	const char	*fmt = "hey %#x %#X %+d % d nice\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, 42, 42, 42, 42);
	sprintf(refbuf, fmt, 42, 42, 42, 42);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_flag_with_width)
{
	const char	*fmt = "hey %-#42x %#042X %+023d %- 54d nice\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, 42, 42, 42, 42);
	sprintf(refbuf, fmt, 42, 42, 42, 42);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_flag_with_prec)
{
	const char	*fmt = "hey %-#.42x %#0.X %+0.23d %- .d nice\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, 42, 42, 42, 0);
	sprintf(refbuf, fmt, 42, 42, 42, 0);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_prec_width_flag)
{
	const char	*fmt = "hey %-#23.42x %#012.X %+032.23d %- 23.d nice\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, 42, 42, 42, 0);
	sprintf(refbuf, fmt, 42, 42, 42, 0);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_lenspec_min)
{
	const long long	nbs[] = {
		INT_MIN,
		LONG_MIN,
		CHAR_MIN,
		SHRT_MIN,
	};
	const char	*fmt = "1:%d 2:%ld 3:%hhd 4:%hd";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);
	sprintf(refbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_lenspec_2)
{
	const long long	nbs[] = {
		UINT_MAX,
		ULONG_MAX,
		UCHAR_MAX,
		USHRT_MAX,
	};
	const char	*fmt = "1:%u 2:%lu 3:%hhu 4:%hu(yolo)\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);
	sprintf(refbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_lenspec_with_flags)
{
	const long long	nbs[] = {
		INT_MAX,
		LONG_MAX,
		UCHAR_MAX,
		USHRT_MAX,
		0,
	};
	const char	*fmt = "1:%+d 2:% 54ld 3:%15.5hhu 4:%54hu 5: %52.0lld(yolo)\n";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3], nbs[4]);
	sprintf(refbuf, fmt, nbs[0], nbs[1], nbs[2], nbs[3], nbs[4]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_star_1)
{
	const int	stars[] = {
		42,
		23,
		42,
		32,
		56,
		45,
	};
	const int	nbs[] = {
		INT_MAX,
		0,
		INT_MIN,
		42,
	};
	const char	*fmt = "1:%*.*x 2:%*.4x 3:%5.*x 4:%*.*x";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, stars[0], stars[1], nbs[0], stars[2], nbs[1], stars[3], nbs[2], stars[4], stars[5], nbs[3]);
	sprintf(refbuf, fmt, stars[0], stars[1], nbs[0], stars[2], nbs[1], stars[3], nbs[2], stars[4], stars[5], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_star_2)
{
	const int	stars[] = {
		-32,
		23,
		-42,
		32,
		56,
		-64,
	};
	const int	nbs[] = {
		INT_MAX,
		42,
		INT_MIN,
		0,
	};
	const char	*fmt = "1:%*.*x 2:%*.4x 3:%5.*x 4:%*.*d";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, stars[0], stars[1], nbs[0], stars[2], nbs[1], stars[3], nbs[2], stars[4], stars[5], nbs[3]);
	sprintf(refbuf, fmt, stars[0], stars[1], nbs[0], stars[2], nbs[1], stars[3], nbs[2], stars[4], stars[5], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}

Test(ft_printf, test_star_ultimate)
{
	const int	stars[] = {
		-32,
		23,
		-42,
		32,
		56,
		-64,
	};
	const int	nbs[] = {
		INT_MAX,
		42,
		INT_MIN,
		0,
	};
	const char	*fmt = "1:%#-*.*lx 2:%#*.4hhx 3:%#5.*llx 4:% *.*hhd";
	char		refbuf[MAX_BUF];
	char		ftbuf[MAX_BUF];

	ft_sprintf(ftbuf, fmt, stars[0], stars[1], nbs[0], stars[2], nbs[1], stars[3], nbs[2], stars[4], stars[5], nbs[3]);
	sprintf(refbuf, fmt, stars[0], stars[1], nbs[0], stars[2], nbs[1], stars[3], nbs[2], stars[4], stars[5], nbs[3]);

	cr_expect_str_eq(ftbuf, refbuf);
}
