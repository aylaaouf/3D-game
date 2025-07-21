/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:46:59 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/21 08:44:32 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
		if (!buffer)
		{
			free(temp_buffer);
			return (NULL);
		}
	}
	free(temp_buffer);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	char	*new_line_pos;
	size_t	len;
	size_t	i;

	if (!buffer || !*buffer)
		return (NULL);
	new_line_pos = ft_strchr(buffer, '\n');
	if (new_line_pos)
		len = new_line_pos - buffer + 1;
	else
		len = ft_strlen(buffer);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (free(line), NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	char	*new_line_pos;

	new_line_pos = ft_strchr(buffer, '\n');
	if (!new_line_pos)
		return (NULL);
	new_buffer = ft_strdup(new_line_pos + 1);
	if (!new_buffer)
		return (NULL);
	free(buffer);
	return (new_buffer);
}

static char	*free_buffer(char *buffer)
{
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*new_buffer;

	if (!helper_a(fd, buffer))
	{
		buffer = NULL;
		return (NULL);
	}
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	new_buffer = update_buffer(buffer);
	if (!new_buffer)
		buffer = free_buffer(buffer);
	else
		buffer = new_buffer;
	return (line);
}
