/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:14:37 by janrodri          #+#    #+#             */
/*   Updated: 2025/11/06 15:12:29 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* LENGTH

Returns the chars inside a string, minus the '\0'.
 */
int	length(char *buffer)
{
	int	i;

	if (!buffer)
		return (0);
	i = 0;
	while (buffer[i] != '\0')
		i++;
	return (i);
}
/*STR_CAT

Copies 'read_buffer' in 'line_buffer'. Copies the original content as long as
there are chars inside of it or it has not arrived to a '\n'.

Returns the original lenght of 'read_content', to compare the chars obtained
in 'line_buffer' with this length. If the are equal, everything copied 
succesfully. If they differ, it means that '\n' was found in the middle and it 
stopped copying the found chars after the new line sign. */

int	str_cat(char **new_buffer, char **ref_buffer)
{
	int		i;
	int		j;
	int		len_ref;
	int		len_new;
	char	*temp_new;

	len_ref = length(*ref_buffer);
	len_new = length(*new_buffer);
	temp_new = malloc(len_new + 1);
	str_i_copy(*new_buffer, temp_new, 0);
	free(*new_buffer);
	*new_buffer = malloc(len_ref + len_new + 1);
	if (!(*new_buffer))
		return (-1);
	i = 0;
	while (temp_new[i] != '\0')
		(*new_buffer)[i] = temp_new[i++];
	j = 0;
	while (((*ref_buffer)[j] != '\0') && ((*ref_buffer)[j] != '\n'))
		(*new_buffer)[i++] = (*ref_buffer)[j++];
	(*new_buffer)[i] = '\0';
	free(temp_new);
	return (len_ref + len_new);
}

/*STR_I_COPY 

Starts to copy since the specified index in the buffer that is going
to be filled. The reference is always going to be fully copied. 
Yo can either start the content of copy using the 0 index or
start the copy in a different part of the string. */
char	*str_i_copy(char *ref, char *copy, int copy_index)
{
	int	i;
	
	if (!ref || !copy || copy_index < 0)
		return (NULL);
	i = 0;
	while (ref[i] != '\0' && copy)
	{
		copy[i + copy_index] = ref[i];
		i++;
	}
	copy[i + copy_index] = '\0';
	return (copy);
}

void init(char	**read_buffer, int *read_length, char	**filling_line)
{
	if (!(*read_buffer))
	{
		(*read_buffer) = malloc(BUFFER_SIZE + 1);
		if (!(*read_buffer))
			*read_buffer = NULL;
		(*read_buffer)[BUFFER_SIZE] = '\0';
	}
	if (!(*read_length))
		*read_length = 0;
	if (!(*filling_line));
		*filling_line = NULL;
	return ;
}
/* FOUND_NEWLINE: 

Returns the index of the char '\n' if found in 'read_buffer'.
If not, returns -1. Analyze later if the -1 is because the
newline is in further chars of because it is the end of the file.

Beware with the (*read_buffer) because if you don't put it the 
interpretation varies. You need to work with a char *, so adapt it.*/

int found_newline(char **read_buffer)
{
	int i;

	i = 0;
	while ((*read_buffer)[i] != '\0')
	{
		if ((*read_buffer)[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
