/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:44:58 by ayelasef          #+#    #+#             */
/*   Updated: 2025/07/29 21:59:42 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void put_pixel_img(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    int idx = y * game->size_line + x * (game->bpp / 8);
    *(unsigned int *)(game->img_data + idx) = color;
}

void raycast(t_game *game)
{
    for (int x = RESERVED_WIDTH; x < SCREEN_WIDTH; x++)
    {
        double camera_x = 2 * (x - RESERVED_WIDTH) / (double)(SCREEN_WIDTH - RESERVED_WIDTH) - 1;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

        int map_x = (int)game->player.x;
        int map_y = (int)game->player.y;

        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

        double side_dist_x, side_dist_y;
        int step_x, step_y;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
        }

        int hit = 0;
        int side;
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (game->map->map[map_y][map_x] == '1')
                hit = 1;
        }

        double perp_wall_dist = (side == 0)
            ? (map_x - game->player.x + (1 - step_x) / 2.0) / ray_dir_x
            : (map_y - game->player.y + (1 - step_y) / 2.0) / ray_dir_y;

        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;

        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;

        // Draw ceiling
        for (int y = 0; y < draw_start; y++)
            put_pixel_img(game, x, y, 0x87CEEB);

        // === TEXTURED WALL SLICE ===
        if (game->wall_texture)
        {
            double wall_x;
            if (side == 0)
                wall_x = game->player.y + perp_wall_dist * ray_dir_y;
            else
                wall_x = game->player.x + perp_wall_dist * ray_dir_x;
            wall_x -= floor(wall_x);

            int tex_x = (int)(wall_x * (double)game->wall_texture->width);
            if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
                tex_x = game->wall_texture->width - tex_x - 1;

            double step = 1.0 * game->wall_texture->height / line_height;
            double tex_pos = (double)(draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;

            for (int y = draw_start; y <= draw_end; y++)
            {
                int tex_y = (int)tex_pos & (game->wall_texture->height - 1);
                tex_pos += step;
                int color = get_texture_pixel(game->wall_texture, tex_x, tex_y);
                if (side == 1)
                    color = (color >> 1) & 0x7F7F7F;
                put_pixel_img(game, x, y, color);
            }
        }
        else
        {
            int color = (side == 1) ? 0x00FF00 : 0x0000FF;
            for (int y = draw_start; y <= draw_end; y++)
                put_pixel_img(game, x, y, color);
        }

        // Draw floor
        for (int y = draw_end + 1; y < SCREEN_HEIGHT; y++)
            put_pixel_img(game, x, y, 0xFFFFFF);
    }
}
