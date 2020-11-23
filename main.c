#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
	char *line;
	int fd;
	int bytes;

	bytes = 1;
	fd = open("test/3.txt", O_RDONLY);
	while (bytes == 1)
	{
		bytes = get_next_line(fd, &line);
		printf("|bytes %d|%s\n",bytes, line);
		free(line);
	}
	close(fd);
}
