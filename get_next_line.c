/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:31:58 by janrodri          #+#    #+#             */
/*   Updated: 2025/10/29 19:40:11 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
Notes:----------------------------------------------
The amount of BUFFER_SIZE can be totally arbitrari.
This doesn't mean that you have to return a single buffer with the amount
of BUFFER_SIZE. Internally, you will have to keep reading into a 
buffer[BUFFER_SIZE] and storing that content into a line_buffer[line_size]
until you get all the chars before the '\n'/EOF sign. 

Notes:---------------------------------------------------
The static variables,even though you may call the function multiple times,
they are initialized ONLY ONCE. After they get content inside, they are no 
longer executing the initialization lines of code after that. 
*/

char	*get_next_line(int fd)
{
	static char		*line_buffer;
	char			*read_buffer;
	char			*left_line_buffer;
	int				line_len;
	int				read_copied;

	line_len = line_size(fd);
	line_buffer = NULL;
	read_buffer = read_buffer_size(fd, line_len);
	if (!read_buffer)
		return (NULL);
	if (!line_buffer)
		line_buffer = malloc(line_len + 1);// + 1 ??
	read_copied = str_copy(line_buffer, read_buffer);
	if (read_copied < line_len)
	{
		free(read_buffer);
		get_next_line(fd);
	}
	}

/* #include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	
	return (0);
} */
