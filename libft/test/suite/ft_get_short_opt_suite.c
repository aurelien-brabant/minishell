#include <criterion/criterion.h>

#include "libft/core.h"

TestSuite(ft_get_short_opt);

Test(ft_get_short_opt, test_separated_op)
{
	const char	*argv[] = { NULL, "-c", "-k", "-b", "-a", "-v" };
	int			argc = 6;
	const char	*opstring = "cvakb";
	const char	*expected = "ckbav";
	char		*optarg = NULL;

	int ret;
	while ((ret = ft_get_short_opt(argc, argv, opstring, &optarg)) != -1)
	{
		cr_assert_eq(*expected, ret, "expected: %c, actual: %c", *expected, ret);
		++expected;
	}
	cr_assert_eq('\0', *expected);
}

Test(ft_get_short_opt, test_multiple_op_inside_one_string)
{
	const char	*argv[] = { NULL, "-cav", "-kb" };
	int			argc = 3;
	const char	*opstring = "cvakb";
	const char	*expected = "cavkb";
	char		*optarg = NULL;

	int ret;
	while ((ret = ft_get_short_opt(argc, argv, opstring, &optarg)) != -1)
	{
		cr_assert_eq(*expected, ret, "expected: %c, actual: %c", *expected, ret);
		++expected;
	}
	cr_assert_eq('\0', *expected);
}

Test(ft_get_short_opt, test_mix)
{
	const char	*argv[] = { NULL, "-c", "-a", "-v", "-kb", "zx" };
	int			argc = 6;
	const char	*opstring = "cvakb";
	const char	*expected = "cavkb";
	char		*optarg = NULL;

	int ret;
	while ((ret = ft_get_short_opt(argc, argv, opstring, &optarg)) != -1)
	{
		cr_assert_eq(*expected, ret, "expected: %c, actual: %c", *expected, ret);
		++expected;
	}
	cr_assert_eq('\0', *expected);
}

Test(ft_get_short_opt, test_unknown_opt)
{
	const char	*argv[] = { NULL, "-c", "-a", "-v", "-kb", "-zx" };
	int			argc = 6;
	const char	*opstring = "cvakb";
	const char	*expected = "cavkb";
	char		*optarg = NULL;

	int ret;
	size_t	i = 0;
	while ((ret = ft_get_short_opt(argc, argv, opstring, &optarg)) != -1)
	{
		/* 5th and 6th options are unknown - they are not in opstring */
		if (i >= 5 && i <= 6)
			cr_assert_eq('?', ret);
		else
		{
			cr_assert_eq(*expected, ret, "expected: %c, actual: %c", *expected, ret);
			++expected;
		}
		++i;
	}
	cr_assert_eq('\0', *expected);
}

Test(ft_get_short_opt, test_no_parsable_opt)
{
	const char	*argv[] = { NULL, "he-clo", "world-a", "hey-x", "this", "ho" };
	int			argc = 6;
	const char	*opstring = "cvakb";
	char		*optarg = NULL;

	int ret;
	while ((ret = ft_get_short_opt(argc, argv, opstring, &optarg)) != -1)
		cr_assert_fail("No option should have been detected, BUT ft_get_short_opt returned %c", ret);
}
