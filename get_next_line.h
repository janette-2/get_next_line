/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:20:14 by janrodri          #+#    #+#             */
/*   Updated: 2025/11/05 23:19:16 by janrodri         ###   ########.fr       */
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
int		length(char *buffer);
int		str_cat(char **new_buffer, char **ref_buffer);
char	*str_i_copy(char *ref, char *copy, int copy_index);
void	init(char	**read_buffer, int *read_length, char	**filling_line);
int		found_newline(char **read_buffer);

#endif