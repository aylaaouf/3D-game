/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:05:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/07/29 11:15:40 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void init_color(t_color *color, int r, int g, int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}

void init_config(t_config *config)
{
    config->no = NULL;
    config->so = NULL;
    config->we = NULL;
    config->ea = NULL;
    config->f = NULL;
    config->c = NULL;
    init_color(&config->floor, 0, 0, 0);
    init_color(&config->ceil, 0, 0, 0);
}

void	find_and_init_player(t_game *game)
{
	int	y = 0;
	while (game->map->map[y])
	{
		int	x = 0;
		while (game->map->map[y][x])
		{
			char	tile = game->map->map[y][x];
			if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
			{
				init_player(&game->player, x, y, tile);
				game->map->map[y][x] = '0';
				return;
			}
			x++;
		}
		y++;
	}
	fprintf(stderr, "Error: Player not found in map!\n");
	exit(1);
}

void init_player(t_player *player, int x, int y, char dir)
{
    player->x = x + 0.5;
    player->y = y + 0.5;

    if (dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if (dir == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if (dir == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (dir == 'W')
    {
        player->dir_x = -1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
}
