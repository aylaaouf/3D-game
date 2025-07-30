/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:18:52 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/30 16:40:03 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	has_cub_extension(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (extension == NULL)
		return (ft_putendl_fd(INVALID_PATH, 2), 1);
	if (strcmp(extension, ".cub") == 0)
		return (0);
	else
		return (ft_putendl_fd(INVALID_EXT, 2), 1);
}

int	count_map_lines(char *path)
{
	int		fd;
	int		counter;
	char	*line;

	fd = open(path, O_RDONLY);
	counter = 0;
	line = get_next_line(fd);
	if (fd < 0)
		return (perror("open"), 1);
	while (line)
	{
		if (line[0] == '1' || line[0] == ' ')
			counter++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (counter);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '\n' || line[i] == '\0');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	player_error(int player)
{
	if (player != 1)
	{
		if (player == 0)
			ft_putendl_fd(NO_PLAYER_FOUND, 2);
		else
			ft_putendl_fd(MULTI_PLAYERS, 2);
		return (1);
	}
	return (0);
}
