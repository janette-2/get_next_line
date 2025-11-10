/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:31:58 by janrodri          #+#    #+#             */
/*   Updated: 2025/11/10 21:45:46 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_into_remain(int fd, char *remain)
{
	char	*buffer;
	int		nb_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	nb_read = 1;
	while (nb_read > 0 && remain && newline_index(remain) == -1)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (free(buffer), NULL);
		if (nb_read > 0)
		{
			buffer[nb_read] = '\0';
			remain = ft_strjoin(remain, buffer, nb_read);
			if (!remain)
				return (free(buffer), NULL);
		}
	}
	free(buffer);
	return (remain);
}

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
	*remain = rest;
	return (line);
}

/* GET_NEXT_LINE

read_into_remain()-----------------------------------------
When it starts, it keeps reading untill the storaged chars(remain) 
contain an '\n' or it finds the EOF. 
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

#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int	fd;
	char *line;
	int	count;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	count = 0;
	while (line && count < 30)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (0);
}
