
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

int main(void)
{
	int		fd;
	char	*buffer_read[75];
	int		read_status;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	printf("%ld\n", SSIZE_MAX);
	while (read_status > 0)
	{
	read_status = read(fd, buffer_read, 75);
	write(1, buffer_read, 75);
	}
	return (0);
}
