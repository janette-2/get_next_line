# include <stdlib.h>
# include <unistd.h>

/* The EOF is identified by the int that read() returns.
If you obtain a 0, there's nothing to read, so you have 
finished the file. 
If you get a -1, there is an error with the file or
it doesn't exist. */

int line_size(int fd)
{
	int	size;
	int read_bytes;
	char *read_one;

	size = 0;
	read_one = malloc(2);
	if (!read_one)
		return (0);
	read_bytes = 1;
	while (read_one[0] != '\n' && read_bytes == 1)
	{
		size++;
		read_bytes = read(fd, read_one, 1);
	}
	return (size);
}
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	printf("Tamaño: %d\n", line_size(fd));
	printf("Tamaño: %d\n", line_size(fd));
	printf("Tamaño: %d\n", line_size(fd));
	printf("Tamaño: %d\n", line_size(fd));
	printf("Tamaño: %d\n", line_size(fd));

	return (0);
}
