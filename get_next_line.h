/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:20:14 by janrodri          #+#    #+#             */
/*   Updated: 2025/10/29 21:11:40 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 75
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		line_size(int fd);
char	*read_buffer_size(int fd, int line_size);
size_t	str_cat(char *line_buffer, char *read_buffer);


#endif