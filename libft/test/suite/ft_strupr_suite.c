#include <criterion/criterion.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

Test(ft_strupr, test_basic)
{
	char	*ref = "THIS IS A UPPERCASE STRING WITH lowercase too";
	char	refbuf[100];
	char	*upper_ver = NULL;
	size_t	i = -1;

	strcpy(refbuf, ref);
	upper_ver = strdup(refbuf);
	ft_strupr(upper_ver);
	while (refbuf[++i])
	{
		refbuf[i] = toupper(refbuf[i]);
	}
	cr_assert(strcmp(refbuf, upper_ver) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, upper_ver, refbuf);
}

Test(ft_strupr, test_various_chars)
{
	char	refbuf[] = "%@r93i9Upper ekeokrokr LOWER rkoerk lep@#$%^&&``~~";
	char	ref[100];
	char	*upper_ver = NULL;
	size_t	i = -1;

	strcpy(refbuf, ref);
	upper_ver = strdup(refbuf);
	ft_strupr(upper_ver);
	while (refbuf[++i])
	{
		refbuf[i] = toupper(refbuf[i]);
	}
	cr_assert(strcmp(refbuf, upper_ver) == 0, "For buf=\"%s\":\nWas:\"%s\"\nExpected:\"%s\"", ref, upper_ver, refbuf);
}
