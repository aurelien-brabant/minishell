#include <criterion/criterion.h>
#include "libft.h"

TestSuite(ft_cla_int_suite);

Test(ft_cla_int_suite, test_present)
{
	int ac = 2;
	char *av[] = {
		"progname", "--int=42",
	};
	void *cla = ft_cla_init(ac, av);
	long long int var;

	long long int ret = ft_cla_int_var(cla, &var, "int", -42);

	/* check the result */
	cr_expect_eq(var, 42);
	/* check the return value */
	cr_expect_eq(var, ret);

	free(cla);
}

Test(ft_cla_int_suite, test_default)
{
	int ac = 2;
	char *av[] = {
		"progname", "--eint=42",
	};
	void *cla = ft_cla_init(ac, av);
	long long int var;

	long long int ret = ft_cla_int_var(cla, &var, "int", -42);

	/* check the result */
	cr_expect_eq(var, -42);
	/* check the return value */
	cr_expect_eq(var, ret);

	free(cla);
}
