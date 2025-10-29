/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:38:47 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/10/30 00:02:14 by aylaaouf         ###   ########.fr       */
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

static int	set_identifier(char **field, char *line, int offset)
{
	if (*field)
		free(*field);
	*field = ft_strdup(line + offset);
	return (1);
}

static int	process_identifier(char *line, t_game *game, int *flag)
{
	char	*newline;

	newline = ft_strrchr(line, '\n');
	if (newline)
		*newline = '\0';
	if (!ft_strncmp(line, "NO ", 3))
		*flag += set_identifier(&game->config->no, line, 3);
	else if (!ft_strncmp(line, "SO ", 3))
		*flag += set_identifier(&game->config->so, line, 3);
	else if (!ft_strncmp(line, "WE ", 3))
		*flag += set_identifier(&game->config->we, line, 3);
	else if (!ft_strncmp(line, "EA ", 3))
		*flag += set_identifier(&game->config->ea, line, 3);
	else if (!ft_strncmp(line, "F ", 2))
		*flag += set_identifier(&game->config->f, line, 2);
	else if (!ft_strncmp(line, "C ", 2))
		*flag += set_identifier(&game->config->c, line, 2);
	else if (!ft_strncmp(line, "1", 1))
		return (0);
	else
		return (ft_putendl_fd(INVALID_CHAR_MAP, 2), 1);
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
