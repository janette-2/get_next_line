/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:14:37 by janrodri          #+#    #+#             */
/*   Updated: 2025/11/26 12:49:45 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* FT_STRLEN:

Returns the length of the buffer, without the closing \0 */

int	ft_strlen(char *buffer)
{
	int	i;

	if (!buffer)
		return (0);
	i = 0;
	while (buffer[i] != '\0')
		i++;
	return (i);
}

/* FT_STRDUP:

Returns a duplicated buffer of 'src'*/

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;

	if (!src)
		return (NULL);
	dup = malloc(ft_strlen(src) + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/* NEWLINE_INDEX:

Looks for \n in the passed buffer. When found, returns the index of
it's position (starting at i = 0). If it's not found, returns -1. */

int	newline_index(char *remain)
{
	int	i;

	i = 0;
	while (remain[i])
	{
		if (remain[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

/* FT_STRJOIN
 
Maintains all the content from s1 and appends 
len2 bytes from s2 at the end of s1. 

 Note: ---------------------------------
 ft_strjoin takes ownership of s1 and frees it;
 caller should not use s1 after calling ft_strjoin
 unless the caller assigns s1 to the returned string,
 transforming s1 to a new string, this execution will
 delete the content of the old 's1'. 
 This is because malloc and free work and modify the 
 'heap' memory zone directly. They have a global impact,
 affecting all the functions, when used in a program.
 */

char	*ft_strjoin(char *s1, char *s2, int len2)
{
	int		len1;
	char	*new;
	int		i;
	int		j;

	if (!s2 || len2 < 0 || len2 > ft_strlen(s2))
		return (NULL);
	len1 = ft_strlen(s1);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (j < len1)
	{
		new[j] = s1[j];
		j++;
	}
	i = 0;
	while (j < len1 + len2)
		new[j++] = s2[i++];
	new[j] = '\0';
	free(s1);
	return (new);
}

/* SUBSTR_AND_FREE

Creates a new string out of 's', specifying the start index to copy 
from and the length of the copied content. The function also limits
the copied content to the extends of the real string.
It does not copy further than that, not even if you specify
it like so. */

char	*substr_and_free(char *s, int start, int len)
{
	char			*sub;
	int				i;
	int				s_len;

	if (!s || start < 0 || len < 0)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	free(s);
	return (sub);
}
