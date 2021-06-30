#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_putchar_fd);

Test(ft_putchar_fd, test_ascii_char, .init = cr_redirect_stdout)
{
	ft_putchar_fd('c', STDOUT_FILENO);
	cr_assert_stdout_eq_str("c");
}

Test(ft_putchar_fd, test_greater_than_ascii, .init = cr_redirect_stdout)
{
	ft_putchar_fd((char)0xF4, STDOUT_FILENO);
	cr_assert_stdout_eq_str("\xF4");
}
