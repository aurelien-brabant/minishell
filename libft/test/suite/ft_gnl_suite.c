#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
TestSuite(ft_gnl);

Test(ft_gnl, test_only_filled_lines)
{
	fpos_t	pos;
	int		rt;
	char	refln[1000];
	char	*myln;
	char	*tmp;
	FILE	*fs = fopen("./asset/text/file1.txt", "r");
	int		fd = open("./asset/text/file1.txt", O_RDONLY);
	size_t	ln_to_read = 5;

	if (!fs || fd == -1)
		cr_skip_test("Test file could not be opened, that's not the function fault!");
	for (size_t i = 0; i < ln_to_read; ++i)
	{
		memset(refln, 0, 1000);
		fgets(refln, 1000, fs);
		if ((tmp = strchr(refln, '\n')))
				*tmp = 0;
		rt = ft_gnl(fd, &myln);
		cr_expect_str_eq(myln, refln);
		cr_expect_eq(rt, 1);
	}
	rt = ft_gnl(fd, &myln);
	cr_expect_eq(rt, 0);
	
	/* cleanup */
	free(myln);
	close(fd);
	fclose(fs);
}

Test(ft_gnl, test_filled_with_empty_lines)
{
	fpos_t	pos;
	int		rt;
	char	refln[1000];
	char	*myln;
	char	*tmp;
	FILE	*fs = fopen("./asset/text/file2.txt", "r");
	int		fd = open("./asset/text/file2.txt", O_RDONLY);
	size_t	ln_to_read = 10;

	if (!fs || fd == -1)
		cr_skip_test("Test file could not be opened, that's not the function fault!");
	for (size_t i = 0; i < ln_to_read; ++i)
	{
		memset(refln, 0, 1000);
		fgets(refln, 1000, fs);
		if ((tmp = strchr(refln, '\n')))
				*tmp = 0;
		rt = ft_gnl(fd, &myln);
		cr_expect_str_eq(myln, refln);
		cr_expect_eq(rt, 1);
	}
	rt = ft_gnl(fd, &myln);
	cr_expect_eq(rt, 0);
	
	/* cleanup */
	free(myln);
	close(fd);
	fclose(fs);
}

Test(ft_gnl, test_full_empty_lines)
{
	fpos_t	pos;
	int		rt;
	char	refln[1000];
	char	*myln;
	char	*tmp;
	FILE	*fs = fopen("./asset/text/file3.txt", "r");
	int		fd = open("./asset/text/file3.txt", O_RDONLY);
	size_t	ln_to_read = 10;

	if (!fs || fd == -1)
		cr_skip_test("Test file could not be opened, that's not the function fault!");
	for (size_t i = 0; i < ln_to_read; ++i)
	{
		memset(refln, 0, 1000);
		fgets(refln, 1000, fs);
		if ((tmp = strchr(refln, '\n')))
				*tmp = 0;
		rt = ft_gnl(fd, &myln);
		cr_expect_str_eq(myln, refln);
		cr_expect_eq(rt, 1);
	}
	rt = ft_gnl(fd, &myln);
	cr_expect_eq(rt, 1);
	
	/* cleanup */
	free(myln);
	close(fd);
	fclose(fs);
}

Test(ft_gnl, test_invalid_fd)
{
	int		rt;
	char	*myln = 0;

	rt = ft_gnl(-42, &myln);
	cr_expect_eq(rt, -1);
	
	/* cleanup */
	free(myln);
}

Test(ft_gnl, test_directory_fd)
{
	int		rt;
	char	*myln = 0;
	int		fd = open("./asset", O_RDONLY);

	rt = ft_gnl(fd, &myln);
	cr_expect_eq(rt, -1);
	
	/* cleanup */
	free(myln);
}
