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

#include "cub3d.h"

void	draw_vertical_line(t_game *game, int x, int draw_start, int draw_end, int color)
{
	for (int y = draw_start; y <= draw_end; y++)
		mlx_pixel_put(game->mlx, game->win, x, y, color);
}
void	raycast(t_game *game)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// 1. Calculate ray position and direction
		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

		// 2. Map square the player is in
		int map_x = (int)game->player.x;
		int map_y = (int)game->player.y;

		// 3. Length of ray to next x or y side
		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

		double side_dist_x, side_dist_y;
		int step_x, step_y;

		// 4. Calculate step and initial sideDist
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

		// 5. Perform DDA
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

		// 6. Calculate distance projected on camera direction
		double perp_wall_dist = (side == 0)
			? (map_x - game->player.x + (1 - step_x) / 2.0) / ray_dir_x
			: (map_y - game->player.y + (1 - step_y) / 2.0) / ray_dir_y;

		// 7. Calculate height of line to draw
		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		// 8. Calculate lowest and highest pixel to fill
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;

		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		// 9. Draw ceiling
		for (int y = 0; y < draw_start; y++)
			mlx_pixel_put(game->mlx, game->win, x, y, 0x87CEEB);

		// 10. Draw wall (color can depend on side for shading)
		int color = (side == 1) ? 0x00FF00 : 0x0000FF;
		for (int y = draw_start; y <= draw_end; y++)
			mlx_pixel_put(game->mlx, game->win, x, y, color);

		// 11. Draw floor
		for (int y = draw_end + 1; y < SCREEN_HEIGHT; y++)
			mlx_pixel_put(game->mlx, game->win, x, y, 0xFFFFFF);
	}
}
