#include <criterion/criterion.h>
#include "libft/string.h"
#include "libft/vector.h"

TestSuite(ft_string);

Test(ft_string, ft_string_new_cstr)
{
	const char	*cstr = "Hello world\n";
	char		*actual = NULL;
	t_string str = ft_string_new_cstr(cstr);

	actual = ft_string_tocstring(str);

	cr_expect_str_eq(actual, cstr);
	free(actual);
	ft_string_destroy(str);
}

Test(ft_string, ft_string_new_fill)
{
	const char	*ref = "xxxxxxxxxx";
	char		*actual = NULL;
	t_string str = ft_string_new_fill(10, 'x');

	actual = ft_string_tocstring(str);

	cr_expect_str_eq(actual, ref);
	free(actual);
	ft_string_destroy(str);
}

Test(ft_string, ft_string_append_cstr)
{
	const char	*strs[] = { "Hello", " world", " how", " are", " you ?", NULL };
	char		*ref = "Hello world how are you ?";
	char		*actual = NULL;

	t_string str = ft_string_new_cstr(strs[0]);

	/* append */
	for (size_t i = 1; strs[i] != NULL; ++i) {
		ft_string_append_cstr(str, strs[i]);
	}

	actual = ft_string_tocstring(str);

	cr_expect_str_eq(actual, ref);
	free(actual);
	ft_string_destroy(str);
}

Test(ft_string, ft_string_append)
{
	const char	*strs[] = { "Hello", " world", " how", " are", " you ?" };
	t_string	tstrings[5];
	size_t		nb = sizeof (strs) / sizeof (char *);
	char		*ref = "*** Hello world how are you ?";
	char		*actual = NULL;

	/* Starting tstring */
	t_string str = ft_string_new_cstr("*** ");

	/* create tstrings */
	for (size_t i = 0; i < nb; ++i) {
		tstrings[i] = ft_string_new_cstr(strs[i]);
	}
	/* append tstrings to string */
	for (size_t i = 0; i < nb; ++i) {
		ft_string_append(str, tstrings[i]);
	}

	/* compare with ref */
	actual = ft_string_tocstring(str);
	cr_expect_str_eq(actual, ref);

	/* cleanup */
	free(actual);
	for (size_t i = 0; i < nb; ++i) {
		ft_string_destroy(tstrings[i]);
	}
	ft_string_destroy(str);
}

Test(ft_string, ft_string_at)
{
	const char		*ref = "00000000000";
	char			*actual = NULL;
	t_string		str = ft_string_new_cstr("Hello world");
	
	for (size_t i = 0; i < ft_string_length(str); ++i) {
		*ft_string_at(str, i) = '0';
	}
	actual = ft_string_tocstring(str);
	cr_expect_str_eq(actual, ref);

	free(actual);
	ft_string_destroy(str);
}

Test(ft_string, ft_string_reserve)
{
	const char	*ref = "xxxxxxxxxx";
	const char	*actual = NULL;
	t_string	str = ft_string_new_fill(10, 'x');

	/* ensure capacity is indeed 10 */
	cr_expect_eq(ft_string_capacity(str), 10);

	/* now reserve more */
	ft_string_reserve(str, 50);

	/* ensure it has been reserved properly */
	cr_expect_eq(ft_string_capacity(str), 50);
	actual = ft_string_tocstring(str);
	cr_expect_str_eq(actual, ref);

	/* Try to reserve less than occupied by the string (less than length) */
	ft_string_reserve(str, 9);
	cr_expect_eq(ft_string_capacity(str), 50);

	/* Attempt to write on reserved spaces, just to ensure the space is allocated */
	for (size_t i = 10; i < 50; ++i) {
		*ft_string_at(str, i) = 0;
	}

	free((void *)actual);
	ft_string_destroy(str);
}

Test(ft_string, ft_string_replacechar)
{
	char		*ref = "ababababab";
	char		*actual = NULL;
	t_string	str = ft_string_new_cstr("xbxbxbxbxb");

	ft_string_replacechar(str, 'x', 'a');
	actual = ft_string_tocstring(str);

	cr_expect_str_eq(actual, ref);

	free(actual);
	ft_string_destroy(str);
}

Test(ft_string, ft_string_findchar)
{
	int			ref = 4;
	t_string	str = ft_string_new_cstr("HellO world");

	cr_expect_eq(ft_string_findchar(str, 'O'), ref);
	ref = -1;
	cr_expect_eq(ft_string_findchar(str, 'x'), ref);

	ft_string_destroy(str);
}

Test(ft_string, ft_string_findcsubset)
{
	t_string	str = ft_string_new_cstr("Hello world this is a string");
	const char	*subset = "this is";
	const char	*nosub = "strinG";
	const char	*begsub = "Hello";
	const char	*endsub = "string";
	int	ref = 12; 

	/* test with standard subset */
	cr_expect_eq(ft_string_findcsubset(str, subset), ref);

	/* test with subset at the very beginning */
	cr_expect_eq(ft_string_findcsubset(str, begsub), 0);

	/* test with subset at the very end */
	cr_expect_eq(ft_string_findcsubset(str, endsub), 
			(int)(ft_string_length(str) - strlen(endsub)));

	/* test with missing subset */
	cr_expect_eq(ft_string_findcsubset(str, nosub), -1);

	ft_string_destroy(str);
}

Test(ft_string, ft_string_findsubset)
{
	t_string	str = ft_string_new_cstr("Hello world this is a string");
	t_string	subset = ft_string_new_cstr("this is");
	t_string	nosub = ft_string_new_cstr("strinG");
	t_string 	begsub = ft_string_new_cstr("Hello");
	t_string	endsub = ft_string_new_cstr("string");
	int	ref = 12; 

	/* test with standard subset */
	cr_expect_eq(ft_string_findsubset(str, subset), ref);

	/* test with subset at the very beginning */
	cr_expect_eq(ft_string_findsubset(str, begsub), 0);

	/* test with subset at the very end */
	cr_expect_eq(ft_string_findsubset(str, endsub), 
			(int)(ft_string_length(str) - ft_string_length(endsub)));

	/* test with missing subset */
	cr_expect_eq(ft_string_findcsubset(str, nosub), -1);

	ft_string_destroy(str);
	ft_string_destroy(subset);
	ft_string_destroy(nosub);
	ft_string_destroy(begsub);
	ft_string_destroy(endsub);
}

Test(ft_string, ft_string_subset)
{
	const char	*ref = "ello ";
	char		*actual = NULL;
	t_string	str = ft_string_new_cstr("Hello world !");
	t_string	subset = ft_string_subset(str, 1, 6);

	actual = ft_string_tocstring(subset);
	cr_expect_str_eq(actual, ref);
	free(actual);
	ft_string_destroy(subset);
	subset = ft_string_subset(str, 2, 2);
	cr_expect_null(subset);

	ft_string_destroy(subset);
}

Test(ft_string, ft_string_split)
{
	t_string	str = ft_string_new_cstr("@||Hello |world |how |||@@are @you ?");
	char		*expected = "Hello world how are you ?";
	t_string	joined = ft_string_new(10);
	char		*actual = NULL;

	/* Test standard split with many separators */
	t_vector		split = ft_string_split(str, "@|");
	for (size_t i = 0; i < ft_vector_length(split); ++i)
		ft_string_append(joined, ft_vector_get(split, i));
	actual = ft_string_tocstring(joined);
	cr_expect_str_eq(actual, expected);
	free(actual);
	ft_string_destroy(joined);
	ft_string_destroy_split(split);

	/* Test with no separator */
	split = ft_string_split(str, "");
	actual = ft_string_tocstring(ft_vector_get(split, 0));
	expected = ft_string_tocstring(str);
	cr_expect_str_eq(actual, expected);
	free(actual);
	free(expected);
	ft_string_destroy_split(split);

	ft_string_destroy(str);
}

/*
** Only a simple test is provided, as the logic is the same as in
** ft_btoll, which already has a complete test suite for itself.
*/

Test(ft_string, ft_string_btoll)
{
	t_string	str = ft_string_new_cstr(" -FF");
	bool		err = false;

	cr_expect_eq(ft_string_btoll(str, 16, &err), -255);
	cr_expect_eq(err, false);

	ft_string_destroy(str);

	/* test error: only sign is found */
	str = ft_string_new_cstr("+");

	cr_expect_eq(ft_string_btoll(str, 10, &err), 0);
	cr_expect_eq(err, true);

	ft_string_destroy(str);

	str = ft_string_new_cstr("");
	
	cr_expect_eq(ft_string_btoll(str, 10, &err), 0);

	cr_expect_eq(err, true);
	ft_string_destroy(str);
}

Test(ft_string, ft_string_cmp)
{
	t_string	str1 = ft_string_new_cstr("Hello world");
	t_string	str2 = ft_string_new_cstr("Hello world");

	cr_expect_eq(ft_string_cmp(str1, str2), 0);

	/* change the last character to make str1 less than str2 */
	*ft_string_at(str1, ft_string_length(str1) - 1) = 'D';

	cr_expect(ft_string_cmp(str1, str2) < 0);

	/* back to normal from last test */
	*ft_string_at(str1, ft_string_length(str1) - 1) = 'd';
	/* change the first character of s2 to make it less than str1 */
	*ft_string_at(str2, 0) = '0';

	cr_expect(ft_string_cmp(str1, str2) > 0);

	ft_string_destroy(str1);
	ft_string_destroy(str2);
}

Test(ft_string, ft_string_cstrstr)
{
	t_string	str1 = ft_string_new_cstr("Hello world 1 2 3 4");
	char		*cstr = ft_string_tocstring(str1);
	const char	*needle[] = { "world", "2", "h", "H", "w", "hE", "4", "el", "lo", "be", "ka", "12" };
	size_t		needle_size = sizeof (needle) / sizeof (char *);
	size_t		expected;
	size_t		actual;
	char		*tmp;

	for (size_t i = 0; i < needle_size; ++i) {
		tmp = strstr(cstr, needle[i]); 
		expected = tmp != NULL ? tmp - cstr : -1;
		actual = ft_string_cstrstr(str1, needle[i]);
		cr_expect_eq(expected, actual, "expected=%ld | actual=%ld", expected, actual);
	}
	free(cstr);
	ft_string_destroy(str1);
}

Test(ft_string, ft_string_csubst)
{
	t_string	str1 = ft_string_new_cstr("salusalut a tous salut!! salu salut");
	t_string	substituted = ft_string_csubst(str1, "salut", "hello");
	char		*expected = "saluhello a tous hello!! salu hello";
	char		*actual = ft_string_tocstring(substituted);

	cr_expect_str_eq(expected, actual);
	free(actual);
	ft_string_destroy(substituted);
	ft_string_destroy(str1);
}

Test(ft_string, ft_string_append_char)
{
	t_string	str1 = ft_string_new_cstr("Hello worl");
	char		*expected = "Hello world";
	ft_string_append_char(str1, 'd');
	char		*actual = ft_string_tocstring(str1);

	cr_expect_str_eq(expected, actual);
	free(actual);
	ft_string_destroy(str1);
}
