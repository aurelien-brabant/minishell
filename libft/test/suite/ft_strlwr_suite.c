#include <criterion/criterion.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

TestSuite(ft_strlwr);

Test(ft_strlwr, test_basic)
{
	char	*ref = "THIS IS A UPPERCASE STRING WITH lowercase too";
	char	refbuf[100];
	char	*lower_ver = NULL;
	size_t	i = -1;

	strcpy(refbuf, ref);
	lower_ver = strdup(refbuf);
	ft_strlwr(lower_ver);
	while (refbuf[++i])
	{
		refbuf[i] = tolower(refbuf[i]);
	}
	cr_assert(strcmp(refbuf, lower_ver) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, lower_ver, refbuf);
}

Test(ft_strlwr, test_various_chars)
{
	char	refbuf[] = "%@r93i9Upper ekeokrokr LOWER rkoerk lep@#$%^&&``~~";
	char	ref[100];
	char	*lower_ver = NULL;
	size_t	i = -1;

	strcpy(refbuf, ref);
	lower_ver = strdup(refbuf);
	ft_strlwr(lower_ver);
	while (refbuf[++i])
	{
		refbuf[i] = tolower(refbuf[i]);
	}
	cr_assert(strcmp(refbuf, lower_ver) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, lower_ver, refbuf);
}
