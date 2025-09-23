/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:20:45 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/09/22 15:15:53 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player_char(c) || c == 'P'
		|| c == '\0');
}

static int	handle_map_line(char *line, char **map, int *i)
{
	char	*newline;

	if (line[0] == '1' || line[0] == ' ')
	{
		newline = ft_strrchr(line, '\n');
		if (newline)
			*newline = '\0';
		map[*i] = line;
		(*i)++;
		return (0);
	}
	else if (is_empty_line(line))
	{
		ft_putendl_fd(EMPTY_MAP_LINE, 2);
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

static int	process_map_line(char *line, char **map, int *i, int *map_started)
{
	if (!*map_started && !(line[0] == '1'))
	{
		free(line);
		return (0);
	}
	if (!*map_started && (line[0] == '1'))
		*map_started = 1;
	if (*map_started)
	{
		if (handle_map_line(line, map, i))
			return (1);
	}
	return (0);
}

static int	read_map_loop(int fd, char **map)
{
	char	*line;
	int		map_started;
	int		i;

	map_started = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (process_map_line(line, map, &i, &map_started))
		{
			free_2d(map);
			get_next_line(-1);
			close(fd);
			return (1);
		}
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (0);
}

char	**read_map(char *path)
{
	char	**map;
	int		fd;
	int		total_lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), NULL);
	total_lines = count_map_lines(path);
	if (total_lines <= 0)
		return (close(fd), NULL);
	map = ft_calloc((total_lines + 1), sizeof(char *));
	if (!map)
	{
		ft_putendl_fd(MAP_READ_FAIL, 2);
		close(fd);
		return (NULL);
	}
	if (read_map_loop(fd, map))
	{
		free_2d(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}
