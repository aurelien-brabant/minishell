#include <criterion/criterion.h>
#include <stdbool.h>
#include "libft/stack.h"

TestSuite(ft_stack);

Test(ft_stack, ft_stack_push_pop)
{
	int		tab[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	t_stack	stack = ft_stack_new();
	int	size = sizeof (tab) / sizeof (int);

	for (int i = 0; i < size; ++i) {
		ft_stack_push(stack, &tab[i]);
	}
	while (--size >= 0)
		cr_expect_eq(*(int *)ft_stack_pop(stack), tab[size]);

	ft_stack_destroy(stack, NULL);
}

Test(ft_stack, ft_stack_isempty)
{
	t_stack	stack = ft_stack_new();

	cr_expect_eq(ft_stack_isempty(stack), true);

	ft_stack_destroy(stack, NULL);
}

Test(ft_stack, ft_stack_size)
{
	int		tab[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	t_stack	stack = ft_stack_new();
	size_t	size = sizeof (tab) / sizeof (int);

	for (size_t i = 0; i < size; ++i) {
		ft_stack_push(stack, &tab[i]);
	}
	cr_expect_eq(ft_stack_size(stack), (size_t)size);

	ft_stack_destroy(stack, NULL);
}

Test(ft_stack, ft_stack_peek)
{
	t_stack	stack = ft_stack_new();

	ft_stack_push(stack, "hello world");

	/* Peek should not pop the value */
	cr_expect_str_eq(ft_stack_peek(stack), "hello world");
	cr_expect_str_eq(ft_stack_peek(stack), "hello world");

	ft_stack_destroy(stack, NULL);
}





