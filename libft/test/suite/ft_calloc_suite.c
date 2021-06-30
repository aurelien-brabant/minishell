#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

TestSuite(ft_calloc);

Test(ft_calloc, test_basic)
{
	const size_t	nmemb = 5;
	const size_t	size = 4;
	void			*rfbuf = NULL;
	void			*ftbuf = NULL;

	rfbuf = calloc(nmemb, size);
	ftbuf = ft_calloc(nmemb, size);
	cr_expect(memcmp(rfbuf, ftbuf, nmemb * size) == 0, "The allocated memory has not been set to zero correctly.");
	free(rfbuf);
	free(ftbuf);
}
