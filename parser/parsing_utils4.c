/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:44 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/10/30 00:03:38 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isdegit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == ','))
			return (1);
		i++;
	}
	if (i > 0 && str[i - 1] == ',')
		return (1);
	return (0);
}

int	should_skip_line(char *line)
{
	return (line[0] == '\n');
}

int	is_map_line(char *line)
{
	return (line[0] == '1');
}

int	valid_door(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->map->height = ft_strlen_2d(game->map->map);
	while (i < game->map->height)
	{
		j = 0;
		game->map->last_width = ft_strlen(game->map->map[i]);
		while (j < game->map->last_width)
		{
			if (game->map->map[i][j] == 'P' && check_door_condition(game, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	condition_b(t_game *game, int player)
{
	if (player_error(player))
		return (1);
	if (is_closed(game))
		return (1);
	if (valid_door(game))
		return (write(2, "Invalid door\n", 14), 1);
	return (0);
}
