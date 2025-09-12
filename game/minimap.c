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

void draw_square_minimap(t_game *game, int x, int y, int color)
{
    for (int i = 0; i < MINIMAP_TILE_SIZE; i++)
        for (int j = 0; j < MINIMAP_TILE_SIZE; j++)
            put_pixel_img(game, x + j, y + i, color);
}

void render_minimap(t_game *game)
{
    for (int map_y = 0; map_y < game->map->height; map_y++)
    {
        int width = strlen(game->map->map[map_y]);
        for (int map_x = 0; map_x < width; map_x++)
        {
            char tile = game->map->map[map_y][map_x];
            int color;
            if (tile == '1')
                color = 0x888888; // wall
            else if (tile == 'P' || tile == 'p')
                color = 0xFFA500; // door (orange)
            else if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
                color = 0xCCCCCC; // floor
            else
                continue;
            draw_square_minimap(
                game,
                MINIMAP_OFFSET_X + map_x * MINIMAP_TILE_SIZE,
                MINIMAP_OFFSET_Y + map_y * MINIMAP_TILE_SIZE,
                color
            );
        }
    }
    // Draw player as a red dot
    int px = MINIMAP_OFFSET_X + (int)(game->player.x * MINIMAP_TILE_SIZE);
    int py = MINIMAP_OFFSET_Y + (int)(game->player.y * MINIMAP_TILE_SIZE);
    for (int y = -2; y <= 2; y++)
        for (int x = -2; x <= 2; x++)
            put_pixel_img(game, px + x, py + y, 0xFF0000);
}

int render_frame(t_game *game)
{
    game_loop(game);
    raycast(game);
    render_minimap(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}
