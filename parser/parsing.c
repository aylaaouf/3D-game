/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 06:21:11 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/09/22 14:22:52 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_rgb(char *str, t_color *color)
{
	char	**split_result;

	int (r), (g), b;
	if (!str || !color)
		return (1);
	split_result = ft_split(str, ',');
	if (!split_result || !split_result[0] || !split_result[1]
		|| !split_result[2] || split_result[3] != NULL)
	{
		if (split_result)
			free_2d(split_result);
		return (1);
	}
	r = ft_atoi(split_result[0]);
	g = ft_atoi(split_result[1]);
	b = ft_atoi(split_result[2]);
	free_2d(split_result);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (get_next_line(-1), 1);
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}

int	condition(t_game *game, int i, int j)
{
	if (i == 0 || j == 0 || i == game->map->height - 1
		|| j == game->map->last_width - 1)
		return (1);
	if (game->map->map[i - 1][j] == ' ' || game->map->map[i + 1][j] == ' '
		|| game->map->map[i][j - 1] == ' ' || game->map->map[i][j + 1] == ' '
		|| !game->map->map[i - 1][j] || !game->map->map[i + 1][j]
		|| !game->map->map[i][j - 1] || !game->map->map[i][j + 1])
		return (1);
	return (0);
}

int	is_closed(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	game->map->height = ft_strlen_2d(game->map->map);
	while (i < game->map->height)
	{
		j = 0;
		game->map->last_width = ft_strlen(game->map->map[i]);
		while (j < game->map->last_width)
		{
			c = game->map->map[i][j];
			if (c == '0' || is_player_char(c))
			{
				if (condition(game, i, j))
					return (ft_putendl_fd(MAP_NOT_CLOSED, 2), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_map(t_game *game)
{
	int i, (j), (player);
	player = 0;
	i = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (!is_valid_char(game->map->map[i][j]))
				return (ft_putendl_fd(INVALID_CHAR_MAP, 2), 1);
			if (is_player_char(game->map->map[i][j]))
			{
				game->player.x = j;
				game->player.y = i;
				player++;
			}
			j++;
		}
		i++;
	}
	if (condition_b(game, player))
		return (1);
	return (0);
}

int	parser(int ac, char **av, t_game *game)
{
	int	fd;

	if (ac != 2)
		return (ft_putendl_fd(USAGE_ERR, 2), 1);
	if (has_cub_extension(av[1]))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	if (parse_identifiers(fd, game))
		return ((get_next_line(-1)), 1);
	close(fd);
	if (parse_rgb(game->config->f, &game->config->floor))
		return (ft_putendl_fd(INVALID_FLOOR, 2), 1);
	if (parse_rgb(game->config->c, &game->config->ceil))
		return (ft_putendl_fd(INVALID_CEILING, 2), 1);
	game->map->map = read_map(av[1]);
	if (!game->map->map)
		return (1);
	if (parse_map(game))
	{
		free_2d(game->map->map);
    	return ((game->map->map = NULL), 1);
	}
	return (0);
}
