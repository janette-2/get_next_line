/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:31:58 by janrodri          #+#    #+#             */
/*   Updated: 2025/10/26 18:17:28 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/* The amount of chars in a line is usually 75.
PERO SI LO PUEDES CALCULAR TU MEJOR QUE MEJOR CREO YO?? */
char	*get_next_line(int fd)
{
	static char		*buffer;
	size_t			size;

	size = BUFFER_SIZE;
	if (size == read(fd, buffer, size))
		return (buffer);
	else
		return (NULL);
}

#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("Reference_text_THG.txt", O_RDONLY);
	
	return (0);
}
