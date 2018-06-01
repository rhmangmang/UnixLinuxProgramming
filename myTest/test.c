#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
	int fd;
	char buf[1000];

	fd = open("file", O_RDONLY);
	if (fd == -1) return 1;
	
	int numread = read(fd, buf, 1000);
	
	printf("%d", numread);
	return 0;
}

