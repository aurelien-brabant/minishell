#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strtok);

Test(ft_strtok, test_simple_tokens)
{
	char		ref_str[] = "Hello world how are you";
	char		ft_str[] = "Hello world how are you";
	const char	*delim = " ";
	char		*ref_tok = NULL;
	char		*ft_tok =  NULL;

	ref_tok = strtok(ref_str, delim);
	ft_tok = ft_strtok(ft_str, delim);

	while (ref_tok && ft_tok)
	{
		cr_expect_str_eq(ft_tok, ref_tok);
		ref_tok = strtok(NULL, delim);
		ft_tok = ft_strtok(NULL, delim);
	}
	cr_assert_null(ref_tok);
	cr_assert_null(ft_tok);
}

Test(ft_strtok, test_multiple_delim)
{
	char		ref_str[] = "Hello@@|||   world     h|ow @@@ar e||@ |||yo u";
	char		ft_str[] = "Hello@@|||   world     h|ow @@@ar e||@ |||yo u";
	const char	*delim = " |@";
	char		*ref_tok = NULL;
	char		*ft_tok =  NULL;

	ref_tok = strtok(ref_str, delim);
	ft_tok = ft_strtok(ft_str, delim);
	while (ref_tok && ft_tok)
	{
		cr_expect_str_eq(ft_tok, ref_tok);
		ref_tok = strtok(NULL, delim);
		ft_tok = ft_strtok(NULL, delim);
	}
	cr_assert_null(ref_tok);
	cr_assert_null(ft_tok);
}

Test(ft_strtok, test_only_delim)
{
	char		ref_str[] = "||||||   | |      ||||||";
	char		ft_str[] = "||||||   | |      ||||||";
	const char	*delim = "| ";
	char		*ref_tok = NULL;
	char		*ft_tok =  NULL;

	ref_tok = strtok(ref_str, delim);
	ft_tok = ft_strtok(ft_str, delim);

	while (ref_tok && ft_tok)
	{
		cr_expect_str_eq(ft_tok, ref_tok);
		ref_tok = strtok(NULL, delim);
		ft_tok = ft_strtok(NULL, delim);
	}
	cr_assert_null(ref_tok);
	cr_assert_null(ft_tok);
}

Test(ft_strtok, test_empty_delim)
{
	char		ref_str[] = "Hello world how are you";
	char		ft_str[] = "Hello world how are you";
	const char	*delim = "";
	char		*ref_tok = NULL;
	char		*ft_tok =  NULL;

	ref_tok = strtok(ref_str, delim);
	ft_tok = ft_strtok(ft_str, delim);

	while (ref_tok && ft_tok)
	{
		cr_expect_str_eq(ft_tok, ref_tok);
		ref_tok = strtok(NULL, delim);
		ft_tok = ft_strtok(NULL, delim);
	}
	cr_assert_null(ref_tok);
	cr_assert_null(ft_tok);
}

Test(ft_strtok, test_all_empty)
{
	char		ref_str[] = "";
	char		ft_str[] = "";
	const char	*delim = "";
	char		*ref_tok = NULL;
	char		*ft_tok =  NULL;

	ref_tok = strtok(ref_str, delim);
	ft_tok = ft_strtok(ft_str, delim);

	while (ref_tok && ft_tok)
	{
		cr_expect_str_eq(ft_tok, ref_tok);
		ref_tok = strtok(NULL, delim);
		ft_tok = ft_strtok(NULL, delim);
	}
	cr_assert_null(ref_tok);
	cr_assert_null(ft_tok);
}
