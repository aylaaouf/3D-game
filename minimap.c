/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:32:43 by ayelasef          #+#    #+#             */
/*   Updated: 2025/07/29 12:12:44 by ayelasef         ###   ########.fr       */
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

void render_minimap(t_game *game)
{
    int map_x, map_y;
    map_y = 0;

    while (game->map->map[map_y])
    {
        map_x = 0;
        while (game->map->map[map_y][map_x])
        {
            int color;
            char tile = game->map->map[map_y][map_x];

            if (tile == '1')
                color = 0xFFFFFF;
            else if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
                color = 0x808080;
            else
            {
                map_x++;
                continue;
            }
            draw_square(game, map_x * TILE_SIZE, map_y * TILE_SIZE, color);
            map_x++;
        }
        map_y++;
    }
    int px = (int)(game->player.x * TILE_SIZE);
    int py = (int)(game->player.y * TILE_SIZE);

    for (int y = -2; y <= 2; y++)
    {
        for (int x = -2; x <= 2; x++)
        {
            put_pixel(game, px + x, py + y, 0xFF0000);
        }
    }
}

int render_frame(t_game *game)
{
    // mlx_clear_window(game->mlx, game->win); // optional
    raycast(game);
    render_minimap(game);
    return (0);
}
