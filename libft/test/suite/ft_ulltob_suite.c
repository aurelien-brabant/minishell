#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_ulltob);

Test(ft_ulltob, test_basic)
{
	char		*ref = "45652435";
	long long	lg = 45652435;	
	char		*conv = NULL;
	
	conv = ft_ulltob(lg, 10);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%llu:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_ulltob, test_positive_octal)
{
	char		*ref = "256114723";
	long long	lg = 45652435;	
	char		*conv = NULL;
	
	conv = ft_ulltob(lg, 8);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%llu:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_ulltob, test_positive_binary)
{
	char		*ref = "11111111";
	long long	lg = 255;	
	char		*conv = NULL;
	
	conv = ft_ulltob(lg, 2);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%llu:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_ulltob, test_positive_hex)
{
	char		*ref = "10F9";
	long long	lg = 4345;	
	char		*conv = NULL;
	
	conv = ft_ulltob(lg, 16);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%llu:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_ulltob, test_upper_bound)
{
	char		*ref = "18446744073709551615";
	long long	lg = ULLONG_MAX;	
	char		*conv = NULL;
	
	conv = ft_ulltob(lg, 10);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%llu:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
}

Test(ft_ulltob, test_zero)
{
	char *ref = "0";
	char *ft[4];
	long long lg = 0;
	char	*conv = NULL;

	ft[0] = ft_ulltob(lg, 10);	
	ft[1] = ft_ulltob(lg, 2);	
	ft[2] = ft_ulltob(lg, 16);	
	ft[3] = ft_ulltob(lg, 8);	

	for (size_t i =0; i < 4; ++i)
	{
		cr_expect(strcmp(ft[i], ref) == 0, "Was:\"%s\"\nExpected:\"%s\"", ft[i], ref);
		free(ft[i]);
	}
}
