#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

TestSuite(ft_lltob);

Test(ft_lltob, test_basic)
{
	char		*ref = "45652435";
	long long	lg = 45652435;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 10);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_lltob, test_negative)
{
	char		*ref = "-45652435";
	long long	lg = -45652435;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 10);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_lltob, test_positive_octal)
{
	char		*ref = "256114723";
	long long	lg = 45652435;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 8);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_lltob, test_positive_binary)
{
	char		*ref = "11111111";
	long long	lg = 255;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 2);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_lltob, test_positive_hex)
{
	char		*ref = "10F9";
	long long	lg = 4345;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 16);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_lltob, test_neg_octal)
{
	char		*ref = "-256114723";
	long long	lg = -45652435;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 8);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_lltob, test_neg_binary)
{
	char		*ref = "-11111111";
	long long	lg = -255;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 2);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
	free(conv);
}

Test(ft_lltob, test_neg_hex)
{
	char		*ref = "-10F9";
	long long	lg = -4345;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 16);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
}	

Test(ft_lltob, test_upper_bound)
{
	char		*ref = "9223372036854775807";
	long long	lg = LLONG_MAX;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 10);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
}

Test(ft_lltob, test_lower_bound)
{
	char		*ref = "-9223372036854775808";
	long long	lg = LLONG_MIN;	
	char		*conv = NULL;
	
	conv = ft_lltob(lg, 10);
	cr_expect(strcmp(ref, conv) == 0, "For nb=%lld:\nWas:\"%s\"\nExpected:\"%s\"", lg, conv, ref);
}

Test(ft_lltob, test_zero)
{
	char *ref = "0";
	char *ft[4];
	long long lg = 0;
	char	*conv = NULL;

	ft[0] = ft_lltob(lg, 10);	
	ft[1] = ft_lltob(lg, 2);	
	ft[2] = ft_lltob(lg, 16);	
	ft[3] = ft_lltob(lg, 8);	

	for (size_t i =0; i < 4; ++i)
	{
		cr_expect(strcmp(ft[i], ref) == 0, "Was:\"%s\"\nExpected:\"%s\"", ft[i], ref);
		free(ft[i]);
	}
}
