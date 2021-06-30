#include <criterion/criterion.h>
#include "libft.h"
#include "libft/vector.h"

/*
██╗  ██╗███████╗██╗     ██████╗ ███████╗██████╗ ███████╗
██║  ██║██╔════╝██║     ██╔══██╗██╔════╝██╔══██╗██╔════╝
███████║█████╗  ██║     ██████╔╝█████╗  ██████╔╝███████╗
██╔══██║██╔══╝  ██║     ██╔═══╝ ██╔══╝  ██╔══██╗╚════██║
██║  ██║███████╗███████╗██║     ███████╗██║  ██║███████║
╚═╝  ╚═╝╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝
*/

static int	cmp_uint(void *el1, void *el2)
{
	return (*(int *)el1 - *(int *)el2);
}

/*
████████╗███████╗███████╗████████╗███████╗
╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝
   ██║   █████╗  ███████╗   ██║   ███████╗
   ██║   ██╔══╝  ╚════██║   ██║   ╚════██║
   ██║   ███████╗███████║   ██║   ███████║
   ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝
*/

TestSuite(ft_vector);

/*
** Test vector creation, append, destruction (with resize). If any of these
** functions is not working properly, that's really annoying.
*/

Test(ft_vector, test_vector_core)
{
	t_vector	a;
	int		el[] = { 1, 2, 3, 4, 5 };

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(a, i), el[i]);
	}
	ft_vector_destroy(a, NULL);
}

Test(ft_vector, test_vector_delete)
{
	t_vector	a;
	int		el[] = { 1, 2, 3, 4, 5 };

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	for (size_t i = 0; i < ft_vector_length(a) - 1;) {
		ft_vector_delete(a, i, NULL);
	}
	cr_expect_eq(*(int *)ft_vector_get(a, 0), el[4]);
	ft_vector_destroy(a, NULL);
}

Test(ft_vector, test_vector_delete_fn)
{
	t_vector	a;
	char	*el[] = { "str1", "str2", "str3", "str4", "str5" };

	a = ft_vector_new(sizeof (el) / sizeof (char *));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, strdup(el[i]));
	}
	/* Delete every element expect the last */
	for (size_t i = 0; i < ft_vector_length(a) - 1;) {
		ft_vector_delete(a, i, &free);
	}
	cr_expect_str_eq(ft_vector_get(a, 0), el[4]);
	ft_vector_destroy(a, &free);
}

/*
** Insert the distinctive value -1 at the beginning and the end of the vector,
** as well as in the middle of it.
*/

Test(ft_vector, test_vector_insert)
{
	t_vector	a;
	int		el[] = { 1, 12, 3, 4, 5, 6 };
	int		expected[] = { -1, 1, -1, 12, 3, 4, 5, 6, -1 };
	int		inserted = -1;
	int		actual;

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	ft_vector_insert(a, &inserted, 0);
	ft_vector_insert(a, &inserted, 2);
	ft_vector_insert(a, &inserted, ft_vector_length(a));

	size_t expected_size = sizeof (expected) / sizeof (int); 
	for (size_t i = 0; i < expected_size ; ++i) {
		actual = *(int *)ft_vector_get(a, i);
		cr_expect_eq(actual, expected[i], "for i == %ld (%d != %d)\n", i, actual, expected[i]);
	}
	ft_vector_destroy(a, NULL);
}

/*
** Set all elements of the vector to set, which has the distinctive value -1.
*/

Test(ft_vector, test_vector_set)
{
	t_vector	a;
	int		el[] = { 1, 2, 3, 4, 5 };
	int		set = -1;

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
		ft_vector_set(a, &set, i);
	}
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(a, i), set);
	}
	ft_vector_destroy(a, NULL);
}

/* Test substraction operation */

Test(ft_vector, test_vector_sub)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	subed;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };
	int		subset[] = { 2, 3 };
	int		expected[] = { 1, 4, 5 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (subset) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &subset[i]);
	}
	subed = ft_vector_sub(a, sub, &cmp_uint);
	/* Test subed vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(subed, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(subed, NULL);
}

/* FOREACH TEST: basic sum function */

int	add_to_sum(void *el, int i, void *actual)
{
	(void)i;
	*(int *)actual += *(int *)el;
	return (0);
}

Test(ft_vector, test_vector_foreach)
{
	int		el[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	size_t	sum_up_to = sizeof(el) / sizeof (int);
	int		sum = (sum_up_to * (sum_up_to + 1)) / 2;
	int		actual = 0;
	t_vector	a;

	a = ft_vector_new(sum_up_to);
	for (size_t i = 0; i < sum_up_to; ++i) {
		ft_vector_append(a, &el[i]);
	}
	ft_vector_foreach(a, &add_to_sum, &actual);
	cr_expect_eq(actual, sum, "%d != %d\n", actual, sum);
	ft_vector_destroy(a, NULL);
}

/* INTER operation test */

Test(ft_vector, test_vector_inter)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	subed;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };
	int		subset[] = { 2, 3 };
	int		expected[] = { 2, 3 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (subset) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &subset[i]);
	}
	subed = ft_vector_inter(a, sub, &cmp_uint);
	/* Test subed vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(subed, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(subed, NULL);
}

/* UNION operation test */

Test(ft_vector, test_vector_union)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	_union;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };
	int		subset[] = { 2, 3, 8, 4 };
	int		expected[] = { 1, 2, 3, 4, 5, 8 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (subset) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &subset[i]);
	}
	_union = ft_vector_union(a, sub, &cmp_uint);
	/* Test _union vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(_union, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(_union, NULL);
}

/* DUPLICATION */

Test(ft_vector, test_vector_dup)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	dup;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	dup = ft_vector_dup(a);
	/* Test dup vector */
	for (size_t i = 0; i < ft_vector_length(dup); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(dup, i), el[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(dup, NULL);
}

/* CONCATENATION */

Test(ft_vector, test_vector_concat)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	concat;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };
	int		subset[] = { 2, 3, 8, 4 };
	int		expected[] = { 1, 2, 3, 4, 5, 2, 3, 8, 4 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (subset) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &subset[i]);
	}
	concat = ft_vector_concat(a, sub);
	/* Test concat vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(concat, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(concat, NULL);
}

/* REVERSE */

Test(ft_vector, test_vector_reverse)
{
	t_vector	a;

	int	el[] = { 1, 2, 3, 4, 5 };
	int	expected[] = { 5, 4, 3, 2, 1 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	ft_vector_reverse(a);
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(a, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
}

/* LEFT SHIFT */

Test(ft_vector, test_shift_left)
{
	t_vector	a;

	int	el[] = { 1, 2, 3, 4, 5 };
	int	expected[] = { 4, 5, 0, 0, 0 };
	int	shift_amount = 3;

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	ft_vector_shift(a, -1, shift_amount);
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		/* if expected value is zero, it means tha NULL pointer is expected (not the number zero itself) */
		if (expected[i] == 0)
			cr_expect_null(ft_vector_get(a, i));
		else
			cr_expect_eq(*(int *)ft_vector_get(a, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
}

/* RIGHT SHIFT */

Test(ft_vector, test_right_shift)
{
	t_vector	a;

	int		el[] = { 7, 2, 24, 4, 5 };
	int		expected[] = { 0, 0, 0, 0, 7 };
	size_t	shift_amount = 4;

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	ft_vector_shift(a, 1, shift_amount);
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		/* if expected value is zero, it means tha NULL pointer is expected (not the number zero itself) */
		if (expected[i] == 0)
			cr_expect_null(ft_vector_get(a, i));
		else
			cr_expect_eq(*(int *)ft_vector_get(a, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
}

/* LEFT ROTATE */

Test(ft_vector, test_left_rotate)
{
	t_vector	a;

	int	el[] = { 1, 2, 18, 4, 5 };
	int	expected[] = { 18, 4, 5, 1, 2 };
	int	rot_amount = 2;

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	ft_vector_rotate(a, -1, rot_amount);
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(a, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
}

/* RIGHT ROTATE */

Test(ft_vector, test_right_rotate)
{
	t_vector	a;

	int	el[] = { 1, 2, 3, 43, 5 };
	int	expected[] = { 3, 43, 5, 1, 2 };
	int	rot_amount = 3;

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	ft_vector_rotate(a, 1, rot_amount);
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(a, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
}

/* LINEAR SEARCH */

Test(ft_vector, test_linsearch)
{
	t_vector	a;

	int	el[] = { 54, 12, 3, 32, 5 };
	int	searched = 32;
	int	expected = 3;

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Test one present value */
	cr_expect_eq(ft_vector_linsearch(a, &searched, &cmp_uint), expected);

	/* Test one missing value */
	expected = -1;
	searched = 456;
	cr_expect_eq(ft_vector_linsearch(a, &searched, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);
}

Test(ft_vector, test_uniq)
{
	t_vector	a;

	int	notuniq[] = { 54, 12, 3, 32, 12, 5, 5, 2 };
	int	uniq[] = { 54, 12, 3, 32, 5, 2, 0, 1, 15, 14, 13 };
	int	expected = 4;

	/* test */

	/* TEST NOT UNIQ ARRAY */

	a = ft_vector_new(sizeof (notuniq) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &notuniq[i]);
	}
	cr_expect_eq(ft_vector_uniq(a, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);

	/* TEST UNIQ ARRAY */

	a = ft_vector_new(sizeof (notuniq) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &uniq[i]);
	}
	expected = -1;
	cr_expect_eq(ft_vector_uniq(a, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);
}

/* Sorted insertion in an vector */

Test(ft_vector, test_sinsert)
{
	t_vector	a;
	int		el[] = { 1, 2, 5, 12, 24, 36 };
	int		insert_set[] = { 13, 4, 0, 4 };
	int		expected[] = { 0, 1, 2, 4, 4, 5, 12, 13, 24, 36 };
	int		actual;

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}

	/* The vector should remain sorted even if insert_set is unsorted */
	for (size_t i = 0; i < (int)(sizeof (insert_set) / sizeof (int)); ++i) {
		ft_vector_sinsert(a, &insert_set[i], &cmp_uint);
	}

	size_t expected_size = sizeof (expected) / sizeof (int); 
	for (size_t i = 0; i < expected_size ; ++i) {
		actual = *(int *)ft_vector_get(a, i);
		cr_expect_eq(actual, expected[i], "for i == %ld (%d != %d)\n", i, actual, expected[i]);
	}
	ft_vector_destroy(a, NULL);
}

/* Sorted union */

Test(ft_vector, test_vector_sunion)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	_union;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };
	int		subset[] = { 2, 3, 4, 8 };
	int		expected[] = { 1, 2, 3, 4, 5, 8 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (subset) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &subset[i]);
	}
	_union = ft_vector_sunion(a, sub, &cmp_uint);
	/* Test _union vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(_union, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(_union, NULL);
}

/* Sorted inter */

Test(ft_vector, test_vector_sinter)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	subed;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };
	int		subset[] = { 2, 3 };
	int		expected[] = { 2, 3 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (subset) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &subset[i]);
	}
	subed = ft_vector_sinter(a, sub, &cmp_uint);
	/* Test subed vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(subed, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(subed, NULL);
}

/* Sorted sub */

Test(ft_vector, test_vector_ssub)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	subed;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 4, 5 };
	int		subset[] = { 2, 3, 4 };
	int		expected[] = { 1, 5 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (subset) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &subset[i]);
	}
	subed = ft_vector_ssub(a, sub, &cmp_uint);
	/* Test subed vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(subed, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(subed, NULL);
}

/* Merge sorted vectors */

Test(ft_vector, test_vector_merge)
{
	/* vectors involved in test */

	t_vector	a;
	t_vector	sub;
	t_vector	merged;

	/* reference integer sets */

	int		el[] = { 1, 2, 3, 12, 18, 23, 45 };
	int		el2[] = { 5, 6 };
	int		expected[] = { 1, 2, 3, 5, 6, 12, 18, 23, 45 };

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	sub = ft_vector_new(sizeof (el2) / sizeof (int));
	/* Populate a */
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Populate sub */
	for (size_t i = 0; i < ft_vector_capacity(sub); ++i) {
		ft_vector_append(sub, &el2[i]);
	}
	merged = ft_vector_merge(a, sub, &cmp_uint);
	/* Test merged vector */
	for (size_t i = 0; i < (int)(sizeof (expected) / sizeof (int)); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(merged, i), expected[i]);
	}
	ft_vector_destroy(a, NULL);
	ft_vector_destroy(sub, NULL);
	ft_vector_destroy(merged, NULL);
}

/* BINARY SEARCH */

Test(ft_vector, test_binsearch)
{
	t_vector	a;

	int	el[] = { 3, 5, 12, 32, 54 };
	int	searched = 5;
	int	expected = 1;

	/* test */

	a = ft_vector_new(sizeof (el) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &el[i]);
	}
	/* Test one present value */
	cr_expect_eq(ft_vector_binsearch(a, &searched, &cmp_uint), expected);

	/* Test one missing value */
	expected = -1;
	searched = 456;
	cr_expect_eq(ft_vector_binsearch(a, &searched, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);
}

Test(ft_vector, test_suniq)
{
	t_vector	a;

	int	notuniq[] = { 1, 2, 3, 3, 4, 5, 12, 14, 18 };
	int	uniq[] = { 1, 2, 3, 4, 7, 8, 11, 13, 15, 17, 21 };
	int	expected = 3;

	/* test */

	/* TEST NOT UNIQ ARRAY */

	a = ft_vector_new(sizeof (notuniq) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &notuniq[i]);
	}
	cr_expect_eq(ft_vector_suniq(a, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);

	/* TEST UNIQ ARRAY */

	a = ft_vector_new(sizeof (notuniq) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &uniq[i]);
	}
	expected = -1;
	cr_expect_eq(ft_vector_suniq(a, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);
}

Test(ft_vector, test_issorted)
{
	t_vector	a;

	int	sorted[] = { 3, 5, 12, 32, 54 };
	int	unsorted[] = {3, 4, 3, 12, 32, 53 };
	int	expected = true;

	a = ft_vector_new(sizeof (sorted) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &sorted[i]);
	}
	cr_expect_eq(ft_vector_issorted(a, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);


	a = ft_vector_new(sizeof (unsorted) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &unsorted[i]);
	}
	expected = false;
	cr_expect_eq(ft_vector_issorted(a, &cmp_uint), expected);
	ft_vector_destroy(a, NULL);
}

static int	acmp_uint(void *el, void *el2)
{
	return (**(int **)el - **(int **)el2);
}

Test(ft_vector, test_sort)
{
	t_vector	a;

	int	tab[] = { 454, 2, 0, 0, 2, 25, 456, 1, 9, 3 };
	int	sorted_tab[] = { 0, 0, 1, 2, 2, 3, 9, 25, 454, 456 };

	a = ft_vector_new(sizeof (tab) / sizeof (int));
	for (size_t i = 0; i < ft_vector_capacity(a); ++i) {
		ft_vector_append(a, &tab[i]);
	}
	ft_vector_sort(a, &ft_selection_sort, acmp_uint);
	for (size_t i = 0; i < ft_vector_length(a); ++i) {
		cr_expect_eq(*(int *)ft_vector_get(a, i), sorted_tab[i]);
	}
	ft_vector_destroy(a, NULL);
}

Test(ft_vector, test_last)
{
	t_vector	vector = ft_vector_new(10);
	int tab[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (size_t i = 0; i < 10; ++i) {
		ft_vector_append(vector, &tab[i]);
	}
	cr_assert_eq(*(int *)ft_vector_last(vector), 9);
}

Test(ft_vector, test_get_array)
{
	t_vector	vec = ft_vector_new(10);
	const char	*strs[] = {
		"string1", "string2", "string3", "string4", "string5", NULL
	};
	char		**strings = NULL;

	for (int i = 0; strs[i] != NULL; ++i) {
		ft_vector_append(vec, strdup(strs[i]));	
	}

	strings = (char **)ft_vector_get_array(vec);
	for (int i = 0; strings[i] != NULL; ++i) {
		cr_expect_str_eq(strs[i], strings[i]);
	}
}
