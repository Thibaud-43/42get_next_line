#include "get_next_line.h"
#include<stdio.h>

void main(void)
{
	char	buf[2];
	
	printf("%d", read(open("test/3.txt", O_RDONLY), buf, 0));
	printf("%s", buf);
}
