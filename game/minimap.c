/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:32:43 by ayelasef          #+#    #+#             */
/*   Updated: 2025/08/31 11:04:56 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void render_minimap(t_game *game)
{
    int map_x, map_y, x, y;
    map_y = 0;

    while (game->map->map[map_y])
    {
        map_x = 0;
        while (game->map->map[map_y][map_x])
        {
            char tile = game->map->map[map_y][map_x];

            if (tile == '1')
                draw_square_texture(game, map_x * TILE_SIZE, map_y * TILE_SIZE, game->wall_texture);
            else if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
                draw_square(game, map_x * TILE_SIZE, map_y * TILE_SIZE, 0x808080);
            else
            {
                map_x++;
                continue;
            }
            map_x++;
        }
        map_y++;
    }
    int px = (int)(game->player.x * TILE_SIZE);
    int py = (int)(game->player.y * TILE_SIZE);

	y = -2;
    while (y <= 2)
    {
		x = -2;
        while (x <= 2)
        {
            put_pixel(game, px + x, py + y, 0xFF0000);
			x++;
        }
		y++;
    }
}

int render_frame(t_game *game)
{
    raycast(game);
    render_minimap(game);
    return (0);
}
