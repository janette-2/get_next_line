/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:14:37 by janrodri          #+#    #+#             */
/*   Updated: 2025/10/30 01:15:28 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	if (fd < 0)
		return (NULL);
	size = 0;
	read_one = malloc(1);
	if (!read_one)
		return (0);
	while ((read(fd, read_one, 1) == 1) && read_one[0] != '\n')
		size++;
	return (size);
}
/* READ_BUFFER_SIZE

Creates the read_buffer considering if BUFFER_SIZE is positive,
the line to be read has chars in it and the fd is right. 
Adjust it's size to never extend the length of line_size.

Returns the extracted content.

--->>>>>>>>>>PROBAR SI HAY QUE PONERLE EL '\0' EN EL ULTIMO CHAR DEL READ_BUFFER O NO<<<<<<<<<<----------*/

char	*read_buffer_size(int fd, int line_size)
{
	char	*read_buffer;

	if (BUFFER_SIZE <= 0 || fd < 0 || line_size <= 0)
		return (NULL);
	if (BUFFER_SIZE <= line_size)
	{
		read_buffer = malloc(BUFFER_SIZE);
		if (!read_buffer)
			return (NULL);
		read(fd, read_buffer, BUFFER_SIZE);
		read_buffer[BUFFER_SIZE - 1] = '\0';
	}
	if (BUFFER_SIZE > line_size)
	{
		read_buffer = malloc(line_size);
		if (!read_buffer)
			return (NULL);
		read(fd, read_buffer, line_size);
		read_buffer[line_size - 1] = '\0';
	}
	return (read_buffer);
}
/*STR_COPY 

Copies 'read_buffer' in 'line_buffer'. Copies the original content as long as
there are chars inside of it or it has not arrived to a '\n'.

Returns the original lenght of 'read_content', to compare the chars obtained
in 'line_buffer' with this length. If the are equal, everything copied 
succesfully. If they differ, it means that '\n' was found in the middle and it 
stopped copying the found chars after the new line sign. */

size_t	str_cat(char *line_buffer, char *read_buffer)
{
	size_t	i;
	size_t	j;
	size_t	len_read;
	size_t	len_line;

	len_read = 0;
	while (read_buffer)
		len_read++;
	j = 0;
	while(line_buffer)
		j++;
	len_line = j;
	i = 0;
	while ((read_buffer[i] != '\n') || (read_buffer[i] != '\0'))
		line_buffer[j++] = read_buffer[i++];
	line_buffer[j] = '\0';
	return (len_read + len_line);
}
