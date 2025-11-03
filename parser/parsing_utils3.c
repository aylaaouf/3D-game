/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:38:47 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/11/03 19:08:11 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_door_condition(t_game *g, int i, int j)
{
	if (g->map->map[i][j - 1] != '1' || g->map->map[i][j + 1] != '1')
		return (1);
	if (g->map->map[i - 1][j] == '1' && g->map->map[i + 1][j] == '1'
		&& g->map->map[i][j - 1] == '1' && g->map->map[i][j + 1] == '1')
		return (1);
	if (g->map->map[i - 1][j] == '1' || g->map->map[i + 1][j] == '1')
		return (1);
	return (0);
}

static int	set_identifier(char **field, char *line, int offset, int is_texture)
{
	char	*path;

	if (*field)
		free(*field);
	path = ft_strdup(line + offset);
	if (!path)
		return (0);
	if (is_texture && !validate_texture_path(path))
	{
		free(path);
		return (0);
	}
	*field = path;
	return (1);
}

static int	process_identifier(char *line, t_game *game, int *flag)
{
	char	*newline;
	int		result;

	newline = ft_strrchr(line, '\n');
	if (newline)
		*newline = '\0';
	result = 0;
	if (!ft_strncmp(line, "NO ", 3))
		result = set_identifier(&game->config->no, line, 3, 1);
	else if (!ft_strncmp(line, "SO ", 3))
		result = set_identifier(&game->config->so, line, 3, 1);
	else if (!ft_strncmp(line, "WE ", 3))
		result = set_identifier(&game->config->we, line, 3, 1);
	else if (!ft_strncmp(line, "EA ", 3))
		result = set_identifier(&game->config->ea, line, 3, 1);
	else if (!ft_strncmp(line, "F ", 2))
		result = set_identifier(&game->config->f, line, 2, 0);
	else if (!ft_strncmp(line, "C ", 2))
		result = set_identifier(&game->config->c, line, 2, 0);
	else if (!ft_strncmp(line, "1", 1))
		return (0);
	else
		return (ft_putendl_fd(INVALID_CHAR_MAP, 2), 1);
	if (result == 0)
		return (1);
	*flag += result;
	if (*flag > 6)
		return (ft_putendl_fd(DUPLICATE_ID, 2), 1);
	return (0);
}

int	identifiers_loop(char *line, int fd, t_game *game, int *flag)
{
	line = get_next_line(fd);
	while (line)
	{
		if (should_skip_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_map_line(line))
		{
			free(line);
			break ;
		}
		if (process_identifier(line, game, flag))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_identifiers(int fd, t_game *game)
{
	char	*line;
	int		flag;

	line = NULL;
	flag = 0;
	if (identifiers_loop(line, fd, game, &flag))
		return (1);
	if (!game->config->no || !game->config->so || !game->config->we
		|| !game->config->ea || !game->config->f || !game->config->c)
		return (ft_putendl_fd(MISSING_ID, 2), 1);
	return (0);
}
