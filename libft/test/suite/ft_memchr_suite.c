#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

TestSuite(ft_memchr);

Test(ft_memchr, test_basic)
{
	char	*refstr	= "Hello world";
	void	*ref;
	void	*ft;

	ref = memchr(refstr, 'e', 6);
	ft = ft_memchr(refstr, 'e', 6);

	cr_assert(ref == ft, "For buf \"%s\", considering memchr(buf, 'e', 6):\nWas: %p\nExpected: %p", refstr, ft, ref);
}

Test(ft_memchr, test_zero_len)
{
	char	*refstr	= "Hello world";
	void	*ref;
	void	*ft;

	ref = memchr(refstr, 'e', 0);
	ft = ft_memchr(refstr, 'e', 0);

	cr_assert(ref == ft, "For buf \"%s\", considering memchr(buf, 'e', 0):\nWas: %p\nExpected: %p", refstr, ft, ref);
}

Test(ft_memchr, test_not_in_len)
{
	char	*refstr	= "Hello world";
	void	*ref;
	void	*ft;

	ref = memchr(refstr, 'w', 6);
	ft = ft_memchr(refstr, 'w', 6);

	cr_assert(ref == ft, "For buf \"%s\", considering memchr(buf, 'w', 6):\nWas: %p\nExpected: %p", refstr, ft, ref);
}

Test(ft_memchr, test_is_at_last_len)
{
	char	*refstr	= "Hello world";
	void	*ref;
	void	*ft;

	ref = memchr(refstr, 'w', 7);
	ft = ft_memchr(refstr, 'w', 7);

	cr_assert(ref == ft, "For buf \"%s\", considering memchr(buf, 'w', 7):\nWas: %p\nExpected: %p", refstr, ft, ref);
}

Test(ft_memchr, test_unsigned_cast)
{
	char	*refstr	= "Hello étêî";
	void	*ref;
	void	*ft;

	ref = memchr(refstr, 130, 45);
	ft = ft_memchr(refstr, 130, 45);

	cr_assert(ref == ft, "For buf \"%s\", considering memchr(buf, 130, 45):\nWas: %p\nExpected: %p", refstr, ft, ref);
}
