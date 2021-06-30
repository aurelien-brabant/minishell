#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"
#include "limits.h"
#include <stdio.h>

TestSuite(ft_insertion_sort);

/* COMPARATORS */

static int	cmp_int(void *nb1, void *nb2)
{
	int n1 = *(int *)nb1;
	int n2 = *(int *)nb2;

	if (n1 > n2)
		return (1);
	if (n1 < n2)
		return (-1);
	return (0);
}

static int	cmp_long(void *nb1, void *nb2)
{
	long n1 = *(long *)nb1;
	long n2 = *(long *)nb2;

	if (n1 > n2)
		return (1);
	if (n1 < n2)
		return (-1);
	return (0);
}

static int	cmp_str(void *s1, void *s2)
{
	return (strcmp(*(const char **)s1, *(const char **)s2));
}


/* TESTS */

Test(ft_insertion_sort, sort_int)
{
	int	tab[] = { INT_MAX, 8, 7, 6, 5, 4, 3, 2, 1, -4, INT_MIN, 12, 3 };
	int true_tab[] = { INT_MIN, -4, 1, 2, 3, 3, 4, 5, 6, 7, 8, 12, INT_MAX };

	ft_insertion_sort(tab, 13, sizeof (int), &cmp_int);
	for (int i = 0; i < 13; ++i)
		cr_assert_eq(tab[i], true_tab[i], "tab[i] = %d | true_tab[i] = %d", tab[i], true_tab[i]);
}

Test(ft_insertion_sort, sort_long)
{
	long tab[] = { LONG_MAX, 8, 7, 6, 5, 4, 3, 2, 1, -4, LONG_MIN, 12, 3 };
	long true_tab[] = { LONG_MIN, -4, 1, 2, 3, 3, 4, 5, 6, 7, 8, 12, LONG_MAX };

	ft_insertion_sort(tab, 13, sizeof (long), &cmp_long);
	for (int i = 0; i < 13; ++i)
		cr_assert_eq(tab[i], true_tab[i], "tab[i] = %ld | true_tab[i] = %ld", tab[i], true_tab[i]);
}

Test(ft_insertion_sort, sort_str)
{
	char *tab[] = { "cd", "absolument", "1char", "aberrant" };
	char *true_tab[] = { "1char", "aberrant", "absolument", "cd" };

	ft_insertion_sort(tab, 4, sizeof (char *), &cmp_str);
	for (int i = 0; i < 4; ++i)
		cr_assert_str_eq(tab[i], true_tab[i], "i = %d | tab[i] = %s | true_tab[i] = %s", i, tab[i], true_tab[i]);
}
