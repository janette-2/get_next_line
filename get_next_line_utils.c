/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janrodri <janrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:14:37 by janrodri          #+#    #+#             */
/*   Updated: 2025/11/10 21:20:04 by janrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;

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
 caller should not use s1 after calling ft_strjoin. 
 This is because malloc and free modify the 'heap' directly.
 So they have a global impact when used in a program.
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

Limits the copied content to the extends of the real string. It does not
copy further than that, not even if you specify it like so. */

char *substr_and_free(char *s, int start, int len)
{
	char			*sub;
	int				i;
	int				s_len;

	if (!s || start < 0 || len < 0)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (NULL);
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

