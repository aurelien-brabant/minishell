#include <criterion/criterion.h>
#include "libft.h"

TestSuite(ft_cla_str_suite);

Test(ft_cla_str_suite, test_present)
{
	int		ac = 2;
	char	*av[] = {
		"progname", "--str=mystr",
	};
	void	*cla = ft_cla_init(ac, av);
	char	*var;

	char	*ret = ft_cla_str_var(cla, &var, "str", "default");

	/* check the result */
	cr_expect_str_eq(var, "mystr");
	/* check the return value */
	cr_expect_eq(var, ret);

	free(cla);
}

Test(ft_cla_str_suite, test_default)
{
	int		ac = 2;
	char	*av[] = {
		"progname", "--str=mystr",
	};
	void	*cla = ft_cla_init(ac, av);
	char	*var;

	char	*ret = ft_cla_str_var(cla, &var, "dumbkey", "default");

	/* check the result */
	cr_expect_str_eq(var, "default");
	/* check the return value */
	cr_expect_eq(var, ret);

	free(cla);
}

Test(ft_cla_str_suite, test_spaced_string)
{
	int		ac = 2;
	char	*av[] = {
		"progname", "--str=str with spaces",
	};
	void	*cla = ft_cla_init(ac, av);
	char	*var;

	char	*ret = ft_cla_str_var(cla, &var, "str", "default");

	/* check the result */
	cr_expect_str_eq(var, "str with spaces");
	/* check the return value */
	cr_expect_eq(var, ret);

	free(cla);
}
