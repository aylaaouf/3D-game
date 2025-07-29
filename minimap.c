/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:32:43 by ayelasef          #+#    #+#             */
/*   Updated: 2025/07/28 22:03:43 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"


void put_pixel(t_game *game, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
        return;

    mlx_pixel_put(game->mlx, game->win, x, y, color);
}

void draw_square(t_game *game, int x, int y, int color)
{
	int i, j;

	i = 0;
    while (i < TILE_SIZE)
    {
		j = 0;
        while (j < TILE_SIZE)
        {
            put_pixel(game, x + j, y + i, color);
			j++;
        }
		i++;
    }
}

void	render_minimap(t_game *game)
{
	int	map_x, map_y, px, py;
	map_y = 0;
	while (game->map->map[map_y])
	{
		map_x = 0;
		while (game->map->map[map_y][map_x])
		{
			int	color;
			char	tile = game->map->map[map_y][map_x];
			if (tile == '1')
			{
				color = 0xFFFFFF;
				draw_square(game, map_x * TILE_SIZE, map_y * TILE_SIZE, color);
			}
			else if (tile == 'N' || tile == 'S' 
					|| tile == 'E' || tile == 'W')
			{
				color = 0x808080;
				draw_square(game, map_x * TILE_SIZE, map_y * TILE_SIZE, color);
			}
			else if (tile == '0')
			{
				color = 0x808080;
				draw_square(game, map_x * TILE_SIZE, map_y * TILE_SIZE, color);
			}
			else
			{
				map_x++;
				continue;
			}
			map_x++;
		}
		map_y++;
	}
	px = (int)(game->player.x * TILE_SIZE);
	py = (int)(game->player.y * TILE_SIZE);
    draw_square(game, px, py, 0xFF0000);
}
