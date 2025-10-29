# include <stdlib.h>
# include <unistd.h>

/* LINE_SIZE

Analizes the original text, byte by byte, and returns
the amount of bytes that were found in a single line
before jumping to the next one or before the text ends.

Notes:--------------------------
The EOF is identified by the int that read() returns.
If you obtain a 0, there's nothing to read, so you have 
finished the file. 
If you get a -1, there is an error with the file or
it doesn't exist. 
Notes: -------------------------------
In the while is important to FIRST check if the reading has been done,
with the amount of bytes copied. This will also fill the buffer 
read_one[0] BEFORE analizing the content inside of it.*/

int	line_size(int fd)
{
	int		size;
	char	*read_one;

	size = 0;
	read_one = malloc(1);
	if (!read_one)
		return (0);
	while ((read(fd, read_one, 1) == 1) && read_one[0] != '\n')
		size++;
	return (size);
}
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	int	i;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	i = 0;
	while (i != 26)
	{
		printf("Tamaño: %d\n", line_size(fd));
		i++;
	}
	return (0);
}
