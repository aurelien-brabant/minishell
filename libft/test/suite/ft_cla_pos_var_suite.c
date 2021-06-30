#include <criterion/criterion.h>
#include "libft.h"

TestSuite(ft_cla_pos_var);

Test(ft_cla_pos_var, test_pos)
{
	int ac = 5;
	char *av[] = {
		"progname", "--something", "pos1", "--what", "pos2"
	};
	void *cla = ft_cla_init(ac, av);
	char *var;

	char *ret = ft_cla_pos_var(cla, &var, 0, NULL);

	/* check the result */
	cr_expect_str_eq(var, "pos1");
	/* check the return value */
	cr_expect_eq(var, ret);

	free(cla);
}

Test(ft_cla_pos_var, test_default)
{
	int ac = 3;
	char *av[] = {
		"progname", "--something", "--what",
	};
	void *cla = ft_cla_init(ac, av);
	char *var;

	char *ret = ft_cla_pos_var(cla, &var, 0, NULL);

	/* check the result */
	cr_expect_null(var);
	/* check the return value */
	cr_expect_null(ret);

	free(cla);
}

Test(ft_cla_pos_var, test_pos_gt_one)
{
	int ac = 5;
	char *av[] = {
		"progname", "--something", "pos1", "--what", "pos2"
	};
	void *cla = ft_cla_init(ac, av);
	char *var;

	char *ret = ft_cla_pos_var(cla, &var, 1, NULL);

	/* check the result */
	cr_expect_str_eq(var, "pos2");
	/* check the return value */
	cr_expect_eq(var, ret);

	free(cla);
}
