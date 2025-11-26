/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:31:58 by janrodri          #+#    #+#             */
/*   Updated: 2025/11/26 19:30:47 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* READ_INTO_REMAIN:

Initializes the 'remain' buffer by allocating all the 'read' chars into it. 
The reading keeps on going until a \n or EOF is found inside of 'remain'.

BUFFER FAILS--------------------
In case that the malloc fails when creating the buffer, but remain already
had content inside of it. The data that was storaged becames trash, because 
remain would be set to NULL. In this case, we would need to free the lost 
storaged memory doing (free(remain)) before returning NULL.

READ FAILS ---------------------------
A similar approach is found inside the while that fills remain. In case
that read fails, and if so, it would return -1 of read bytes, then the
filling would stop, and before returning NULL, it would free all the data
that was inside of remain, which would be unusable at that moment of failure.

FT_STRJOIN FAILS------------------------------
In the case that strjoin returns a NULL, in that case the previous remain 
would not have been freed from the trash content that albergates in the memory.
To avoid this, instead of directly assigning NULL to remain, we assing the joined
string into a tmp. If tmp is a NULL we still have the previous content of remain
as it is, so we free this content before assigning NULL to the final remain. 
*/

char	*read_into_remain(int fd, char *remain)
{
	char	*buffer;
	int		nb_read;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remain), NULL);
	nb_read = 1;
	while (nb_read > 0 && remain && newline_index(remain) == -1)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (free(remain), free(buffer), NULL);
		if (nb_read > 0)
		{
			buffer[nb_read] = '\0';
			tmp = ft_strjoin(remain, buffer, nb_read);
			if (!tmp)
				return (free(buffer), free (remain), NULL);
			remain = tmp;
		}
	}
	free(buffer);
	return (remain);
}

/*EXTRACT_LINE_FROM_REMAIN:
 
When the program calls this function 'remain' has either found a \n inside of it,
or it has arrived to the EOF. So, either way, we would already have in 'remain'
the whole line. This function separates the final line, keeps the remain part if 
there are extra characters, or returns the whole content if EOF is found.
It will always clean the content of the whole line from the 'remain' buffer. */

char	*extract_line_from_remain(char **remain)
{
	char	*line;
	int		index;
	int		len;
	char	*rest;

	if (!remain || !*remain)
		return (NULL);
	index = newline_index(*remain);
	if (index == -1)
	{
		line = ft_strdup(*remain);
		free(*remain);
		*remain = NULL;
		return (line);
	}
	len = ft_strlen(*remain);
	if (index + 1 < len)
		rest = ft_strdup(*remain + index + 1);
	else
		rest = NULL;
	line = substr_and_free(*remain, 0, index + 1);
	if (!line)
	{
		free(rest);
		rest = NULL;
	}
	*remain = rest;
	return (line);
}

/* GET_NEXT_LINE

Consist on checking that the 'fd' or BUFFER_SIZE is correct. If so,
it will retain chars in remain in between calls with the static buffer 'remain'.
The purpose of 'remain' is to storage the amount of chars specified by 
'BUFFER_SIZE',(using read_into_remain) in the future calls until a 
whole line is completed.

When we get 'remain', it will have the line inside, so, to substract this line,
maintaining the extra chars that the buffer could have, or returning the whole
line, we get 'line' (using extract_line_from_remain). 

*/

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain)
	{
		remain = ft_strdup("");
		if (!remain)
			return (NULL);
	}
	remain = read_into_remain(fd, remain);
	if (!remain || !*remain)
	{
		if (remain)
			free(remain);
		remain = NULL;
		return (NULL);
	}
	line = extract_line_from_remain(&remain);
	return (line);
}
/* 
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int	fd;
	char *line;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	//--Test with different 'fd' (ex. 0 -> keyboard input)
	//fd = -1;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free (line);
	close(fd);
	return (0);

	//Compile with: 
	//cc -Wall -Werror -Wextra (...)
	// get_next_line.c get_next_line_utils.c  -D BUFFER_SIZE=1 && ./a.out 

} */
