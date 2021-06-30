#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_strinsrt);

Test(ft_strinsrt, test_basic_insert)
{
	char	*ref = "I like chocolate because I don't speak english very well.";
	char	*s1 = "I like because I don't speak english very well.";
	char	*s2 = "chocolate ";
	char	*inserted = NULL;

	inserted = ft_strinsrt(s2, s1, 7);
	cr_expect(strcmp(inserted, ref) == 0, "For s1=\"%s\"; s2=\"%s\"; index=%d\nWas:\"%s\"\nExpected:\"%s\"", s1, s2, 7, inserted, ref);
	free(inserted);
}

Test(ft_strinsrt, test_insert_at_last_index)
{
	const char	*ref = "Hello world Programming in C is good!";
	const char	*s1 = "Hello world!";
	const char	*s2 = " Programming in C is good";
	char		*inserted = NULL;	
	
	inserted = ft_strinsrt(s2, s1, strlen(s1) - 1);
	cr_expect(strcmp(inserted, ref) == 0, "For s1=\"%s\"; s2=\"%s\"; index=%ld\nWas:\"%s\"\nExpected:\"%s\"", s1, s2, strlen(s1) - 1, inserted, ref);
	free(inserted);
}

Test(ft_strinsrt, test_insert_at_first_index)
{
	const char	*ref = "I love segfaults because programming in C is good!";
	const char	*s1 = "I love segfaults because ";
	const char	*s2 = "programming in C is good!";
	char		*inserted = NULL;	
	
	inserted = ft_strinsrt(s1, s2, 0);
	cr_expect(strcmp(inserted, ref) == 0, "For s1=\"%s\"; s2=\"%s\"; index=%d\nWas:\"%s\"\nExpected:\"%s\"", s1, s2, 0, inserted, ref);
	free(inserted);
}
