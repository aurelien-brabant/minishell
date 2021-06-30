#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_putstr_fd);

Test(ft_putstr_fd, test_basic, .init = cr_redirect_stdout)
{
	const char	*ref = "Hello How Are You?";
	const char	*strs[] = {
		"Hello ",
		"How ",
		"Are ",
		"You",
		"?",
		0
	};
	for (size_t i = 0; strs[i]; ++i)
		ft_putstr_fd((char *)strs[i], 1);
	cr_assert_stdout_eq_str(ref);
}

Test(ft_putstr_fd, test_unsigned_cast, .init = cr_redirect_stdout)
{
	const char	*ref = "éllo woré mifâ éntèrtainmeunte";

	ft_putstr_fd((char *)ref, 1);
	cr_assert_stdout_eq_str(ref);
}
