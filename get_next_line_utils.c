/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:14:37 by janrodri          #+#    #+#             */
/*   Updated: 2025/10/29 19:59:05 by janrodri         ###   ########.fr       */
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
		read_buffer = malloc(BUFFER_SIZE + 1);
		if (!read_buffer)
			return (NULL);
		read(fd, read_buffer, BUFFER_SIZE);
	}
	if (BUFFER_SIZE > line_size)
	{
		read_buffer = malloc(line_size + 1);
		if (!read_buffer)
			return (NULL);
		read(fd, read_buffer, line_size);
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

size_t	str_copy(char *line_buffer, char *read_buffer)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (read_buffer)
		len++;
	i = 0;
	while ((read_buffer[i] != '\n') || (read_buffer[i] != '\0'))
	{
		line_buffer[i] = read_buffer[i];
		i++;
	}
	line_buffer[i] = '\0';
	return (len);
}
while (i < read_copied)
if ()
{
	

