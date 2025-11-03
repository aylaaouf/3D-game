/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:32:26 by ayelasef          #+#    #+#             */
/*   Updated: 2025/11/03 18:13:47 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_game(t_game *game)
{
	free_game_resources(game);
	exit(0);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	free(config->no);
	free(config->so);
	free(config->we);
	free(config->ea);
	free(config->f);
	free(config->c);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
}

void	free_game_resources(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_wall_textures(game);
	free_hand_texture(game);
	free_door_texture(game);
	free_floor_texture(game);
	if (game->config)
	{
		free_config(game->config);
		free(game->config);
	}
	if (game->map)
	{
		free_map(game->map);
		free(game->map);
	}
	free_mlx(game);
	free(game);
}

int	init_game(int ac, char **av, t_game **game)
{
	*game = allocate_game();
	if (!*game)
		return (1);
	if (parser(ac, av, *game))
	{
		free_game_resources(*game);
		*game = NULL;
		return (1);
	}
	if (find_and_init_player(*game))
	{
		free_game_resources(*game);
		*game = NULL;
		return (1);
	}
	(*game)->floor = (*game)->config->floor;
	(*game)->ceil = (*game)->config->ceil;
	return (0);
}
