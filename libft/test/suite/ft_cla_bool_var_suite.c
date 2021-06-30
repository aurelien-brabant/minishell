#include <criterion/criterion.h>
#include "libft.h"

TestSuite(ft_cla_bool_suite);

Test(ft_cla_bool_suite, test_present)
{
	int		ac = 2;
	char	*av[] = {
		"progname", "--bool",
	};
	void	*cla = ft_cla_init(ac, av);
	bool	var;

	bool	ret = ft_cla_bool_var(cla, &var, "bool", false);

	/* check the result */
	cr_expect_eq(var, true);
	/* check the return value */
	cr_expect_eq(ret, true);

	free(cla);
}

Test(ft_cla_bool_suite, test_default)
{
	int		ac = 1;
	char	*av[] = {
		"progname"
	};
	void	*cla = ft_cla_init(ac, av);
	bool	var;

	bool	ret = ft_cla_bool_var(cla, &var, "bool", false);

	/* check the result */
	cr_expect_eq(var, false);
	/* check the return value */
	cr_expect_eq(ret, false);

	free(cla);
}

Test(ft_cla_bool_suite, test_default_true)
{
	int		ac = 1;
	char	*av[] = {
		"progname"
	};
	void	*cla = ft_cla_init(ac, av);
	bool	var;

	bool	ret = ft_cla_bool_var(cla, &var, "bool", true);

	/* check the result */
	cr_expect_eq(var, true);
	/* check the return value */
	cr_expect_eq(ret, true);

	free(cla);
}
