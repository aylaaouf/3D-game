/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:23:40 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/21 09:34:32 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	helper_a(int fd, char *buffer)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buffer != NULL)
			free(buffer);
		return (0);
	}
	return (1);
}

char	*ft_strchr_gnl(char *s, int c)
{
	unsigned int	i;

	if (!s)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)(&s[i]));
	return (NULL);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*ptr;
	int		len;
	int		i;

	len = ft_strlen_gnl(s1);
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup_gnl(s2));
	else if (!s2)
		return (ft_strdup_gnl(s1));
	result = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	free((void *)s1);
	return (result);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
