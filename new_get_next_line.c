/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:11:11 by janrodri          #+#    #+#             */
/*   Updated: 2025/11/04 13:11:11 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char *line_in_buffer(int index, char **read_buffer, char **filling_line)
{
	char	*copy_line;

	if (*filling_line)
	{
		copy_line = malloc(length(*filling_line) + index + 1);
		if (!copy_line)
			return (NULL);
		str_cat(copy_line, *filling_line);
		*read_length = str_cat(copy_line, *read_buffer);
		free (*filling_line);
		free (*read_buffer);
	}	
	copy_line = malloc(index + 1);
	if (!(copy_line))
		return (NULL);
	str_i_copy(*read_buffer, copy_line, 0);
	if (index < BUFFER_SIZE - 1 && index > 0)
		read_over_line(*read_buffer, *filling_line);
	free(*read_buffer);
	*read_buffer = NULL;
	return (copy_line);
}

/* ADECUAR A LINE_IN Y READ_UNDER */
static char *read_over_line(char **filling_line, char **read_buffer, int *read_length)
{
	left_read = *read_length - length(*filling_line);
	free(*filling_line);
	*filling_line = malloc (BUFFER_SIZE + 1);
	*filling_line[BUFFER_SIZE] = '\0';
	l = 0;
	while (left_read >= 0 && *read_buffer)
		*filling_line[l++] = *read_buffer[BUFFER_SIZE - (left_read--)];
	
}

static char	*read_under_line (int *read_length, char **read_buffer, char **filling_line, int fd)
{
	int		left_read;
	char	*temp_filled;
	int		l;

	str_cat(*filling_line, *read_buffer);
	while ((found_newline(*filling_line) == -1) && (length(*filling_line) == *read_length))
	{
		free(*read_buffer);
		(*read_buffer) = NULL;
		(*read_buffer) = malloc (BUFFER_SIZE + 1);
		if (!(*read_buffer))
			return (NULL);
		(*read_buffer)[BUFFER_SIZE] = '\0';
		read(fd, *read_buffer, BUFFER_SIZE);
		*read_length = str_cat(*filling_line, *read_buffer);
	}
	str_cat(temp_filled, *filling_line);
	left_read = *read_length - length(*filling_line);
	free(*filling_line);
	*filling_line = malloc (BUFFER_SIZE + 1);
	*filling_line[BUFFER_SIZE] = '\0';
	l = 0;
	while (left_read >= 0 && *read_buffer)
		*filling_line[l++] = *read_buffer[BUFFER_SIZE - (left_read--)];
	return (temp_filled);
}

/* 'read_length' doesn't count the \0 char. */

char	*get_next_line(int fd)
{
	int			index_nl;
	char        *read_buffer;
	char		*temp_line;
	static int  read_length;//static?
	static char *filling_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	init(&read_buffer, &read_length, &filling_line);
	read_length = read(fd, read_buffer, BUFFER_SIZE);
	index_nl = found_newline(&read_buffer, &read_length);
	if ((index_nl == -1) && (read_length == BUFFER_SIZE))
		return (read_under_line(&read_length, &read_buffer, &filling_line, fd));
	if ((index_nl >= 0) && (index_nl <= BUFFER_SIZE - 1))
		return (line_in_buffer(index_nl, &read_buffer, &filling_line));
	return (NULL);
	}


#include <stdio.h>
int main(void)
{

	//------------PRUEBAS FOUND_NEWLINE---------------
	char	*string = "Hola\nMari"; 
	int		i;
	i = found_newline(&string);
	printf("Index: %d\n",i);


	return (0);
}