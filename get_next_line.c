/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:31:58 by janrodri          #+#    #+#             */
/*   Updated: 2025/10/30 13:53:14 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char	*read_over_line(char **line_buffer, int *line_len, int len_copied, char *read_buffer)
{
	char	*temp_line;
	int		left_read;
	
	temp_line = malloc(*line_size);
	if (!temp_line)
		return (NULL);
	str_cat(temp_line, *line_buffer);
	free(*line_buffer);
	//*line_buffer = NULL?;
	left_read = len_copied - *line_size;
	while (left_read > 0)
	{
		(*line_buffer)[left_read - 1] = read_buffer[BUFFER_SIZE - left_read];
		left_read--;
	}
	*line_size = 0;
	return (temp_line);
}

static void	read_under_line(char **line_buffer, int *line_len, char **read_buffer, int fd)
{	
	free(*read_buffer);
	while (!(*line_buffer)[*line_len - 2])
		get_next_line(fd);
	return ;
}

static char	*line_complete(char **line_buffer, int *line_len, char **read_buffer)
{
	char	*temp_line;
	
	temp_line = malloc(*line_size);
	if (!temp_line)
		return (NULL);
	str_cat(temp_line, *line_buffer);
	//falta el \0 en temp_line?
	free(*line_buffer);
	free(read_buffer);
	line_len = 0;
	//LES HACE FALTA A LAS CHAR * PONERLAS A NULL??
	return (temp_line);
}

/* GET_NEXT_LINE

Notes:----------------------------------------------
The amount of BUFFER_SIZE can be totally arbitrari.
This doesn't mean that you have to return a single buffer with the amount
of BUFFER_SIZE. Internally, you will have to keep reading into a 
buffer[BUFFER_SIZE] and storing that content into a line_buffer[line_size]
until you get all the chars before the '\n'/EOF sign. 

Notes:---------------------------------------------------
The static variables,even though you may call the function multiple times,
they are initialized ONLY ONCE. After they get content inside, they are no 
longer executing the initialization lines of code after that. When they are 
first created, the compiler sets them as NULL by default. 
*/

char	*get_next_line(int fd)
{
	static char		*line_buffer;
	static int		line_len;
	char			*read_buffer;
	char			*temp_line;
	int				len_copied;

	line_len = line_size(fd);
	read_buffer = read_buffer_size(fd, line_len);
	if (!read_buffer)
		return (NULL);
	if (!line_buffer)
		line_buffer = malloc(line_len);
	len_copied = str_cat(line_buffer, read_buffer);
	if (len_copied < line_len)
		read_under_line(&line_buffer, &line_len, &read_buffer, fd);
	if (len_copied > line_len)
		temp_line = read_over_line(&line_buffer, &line_len, len_copied, read_buffer);
	temp_line = line_complete();
	return (temp_line);
	}

/* #include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	
	return (0);
} */
