#include <criterion/criterion.h>
#include <stdlib.h>
#include "libft.h"

TestSuite(ft_cla_sanity_check);

Test(ft_cla_sanity_check, test_valid)
{
	int ac = 4;
	char *av[] = {
		"progname", "hello", "--world", "how",
	};
	char err[10000];
	void *cla = ft_cla_init(ac, av);
	t_cla_config conf = ft_cla_get_config();

	/* No configuration setting, everything should be fine */
	cr_expect_eq(ft_cla_sanity_check(cla, &conf, err), true);
	cr_expect_str_eq(err, "");

	free(cla);
}

Test(ft_cla_sanity_check, test_not_enough_pos)
{
	int ac = 4;
	char *av[] = {
		"progname", "hello", "--world", "how",
	};
	char err[10000];
	void *cla = ft_cla_init(ac, av);
	t_cla_config conf = ft_cla_get_config();
	
	conf.min_pos = 3;

	cr_expect_eq(ft_cla_sanity_check(cla, &conf, err), false);
	cr_expect_str_neq(err, "");

	free(cla);
}

Test(ft_cla_sanity_check, test_too_much_pos)
{
	int ac = 4;
	char *av[] = {
		"progname", "hello", "--world", "how",
	};
	char err[10000];
	void *cla = ft_cla_init(ac, av);
	t_cla_config conf = ft_cla_get_config();
	
	conf.max_pos = 1;

	cr_expect_eq(ft_cla_sanity_check(cla, &conf, err), false);
	cr_expect_str_neq(err, "");

	free(cla);
}

Test(ft_cla_sanity_check, test_forbidden_opt)
{
	int ac = 4;
	char *av[] = {
		"progname", "hello", "--world", "how",
	};
	char *allowed_opt[] = {
		"--word", "--waouh", NULL,
	};
	char err[10000];
	void *cla = ft_cla_init(ac, av);
	t_cla_config conf = ft_cla_get_config();
	
	conf.allowed_opt = allowed_opt;

	cr_expect_eq(ft_cla_sanity_check(cla, &conf, err), false);
	cr_expect_str_neq(err, "");

	free(cla);
}

Test(ft_cla_sanity_check, test_allowed_opt)
{
	int ac = 6;
	char *av[] = {
		"progname", "hello", "--world", "how", "--waouh", "hey"
	};
	char *allowed_opt[] = {
		"world", "waouh", NULL
	};
	char err[10000];
	void *cla = ft_cla_init(ac, av);
	t_cla_config conf = ft_cla_get_config();
	
	conf.allowed_opt = allowed_opt;

	cr_expect_eq(ft_cla_sanity_check(cla, &conf, err), true);
	cr_expect_str_eq(err, "");

	free(cla);
}

Test(ft_cla_sanity_check, test_forbidden_pos)
{
	int ac = 6;
	char *av[] = {
		"progname", "hello", "--world", "how", "--waouh", "hey"
	};
	char *allowed_pos[] = {
		"hello", "hey", NULL
	};
	char err[10000];
	void *cla = ft_cla_init(ac, av);
	t_cla_config conf = ft_cla_get_config();
	
	conf.allowed_pos = allowed_pos;

	cr_expect_eq(ft_cla_sanity_check(cla, &conf, err), false);
	cr_expect_str_neq(err, "");

	free(cla);
}

Test(ft_cla_sanity_check, test_allowed_pos)
{
	int ac = 6;
	char *av[] = {
		"progname", "hello", "--world", "how", "--waouh", "hey"
	};
	char *allowed_pos[] = {
		"hello", "hey", "how", NULL
	};
	char err[10000];
	void *cla = ft_cla_init(ac, av);
	t_cla_config conf = ft_cla_get_config();
	
	conf.allowed_pos = allowed_pos;

	cr_expect_eq(ft_cla_sanity_check(cla, &conf, err), true);
	cr_expect_str_eq(err, "");

	free(cla);
}
