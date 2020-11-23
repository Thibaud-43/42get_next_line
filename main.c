#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
	char *line;
	int fd;
	int bytes;
	int i;

	bytes = 1;
	i = 1;
	fd = open("test/1.txt", O_RDONLY);
	while (bytes == 1)
	{
		bytes = get_next_line(fd, &line);
		printf("|LINE %d|(OUT %d)%s\n",i, bytes, line);
		i++;
		free(line);
	}
	close(fd);
}
