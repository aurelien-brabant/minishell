#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int main(void)
{
	DIR	*dir;
	struct dirent	*dp;

	dir = opendir("/");
	while (1)
	{
		dp = readdir(dir);
		if (dp == NULL)
			break ;
		puts(dp->d_name);
	}
}
