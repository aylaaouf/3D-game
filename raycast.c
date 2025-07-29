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
	int x = 0;
	while (x < SCREEN_WIDTH)
	{
		// 1. Calculate ray position and direction
		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

		// 2. Which box of the map we're in
		int map_x = (int)game->player.x;
		int map_y = (int)game->player.y;

		// 3. Length of ray from current position to next x or y side
		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

		// 4. What direction to step in x or y
		int step_x;
		if (ray_dir_x < 0)
			step_x = -1;
		else 
			step_x = 1;
		int step_y;
		if (ray_dir_y < 0)
			step_y = -1;
		else 
			step_y = 1;
		double side_dist_x;
		if (ray_dir_x < 0)
			side_dist_x = (game->player.x - map_x) * delta_dist_x;
		else
			side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
		double side_dist_y;
		if (ray_dir_y < 0)
			side_dist_y = (game->player.y - map_y) * delta_dist_y;
		else
			side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
		// 5. Perform DDA
		int hit = 0;
		int side;
		while (hit == 0)
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
			if (game->map->map[map_y][map_x] == '1') // wall hit
				hit = 1;
		}

		// 6. Calculate distance to wall
		double perp_wall_dist = (side == 0)
			? ((map_x - game->player.x + (1.0 - (double)step_x) / 2.0) / ray_dir_x)
			: ((map_y - game->player.y + (1.0 - (double)step_y) / 2.0) / ray_dir_y);

		// 7. Calculate height of line to draw
		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		// 8. Choose color
		int color;
		if (side == 1)
			color = 0xAAAAAA;
		else
			color = 0xFF0000;
		// 9. Draw ceiling
		for (int y = 0; y < draw_start; y++)
			mlx_pixel_put(game->mlx, game->win, x, y,
				rgb(game->config->ceil.r, game->config->ceil.g, game->config->ceil.b));

		// 10. Draw wall
		draw_vertical_line(game, x, draw_start, draw_end, color);

		// 11. Draw floor
		for (int y = draw_end + 1; y < SCREEN_HEIGHT; y++)
			mlx_pixel_put(game->mlx, game->win, x, y,
				rgb(game->config->floor.r, game->config->floor.g, game->config->floor.b));

		x++;
	}
}

