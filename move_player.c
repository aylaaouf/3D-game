/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:55:36 by ayelasef          #+#    #+#             */
/*   Updated: 2025/07/29 12:11:37 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void redraw_player_only(t_game *game)
{
	int screen_x = game->player.x * TILE_SIZE;
	int screen_y = game->player.y * TILE_SIZE;
	for (int py = 0; py < 4; py++)
	{
		for (int px = 0; px < 4; px++)
		{
			mlx_pixel_put(game->mlx, game->win,
				screen_x + px, screen_y + py, 0xFF0000);
		}
	}
}

int handle_keypress(int keycode, t_game *game)
{
	double move_speed = 0.1;
	double rot_speed = 0.1;
	double new_x, new_y;

	if (keycode == 65307) // ESC
		exit(0);

	// Move Forward
	if (keycode == 'w' || keycode == 65362)
	{
		new_x = game->player.x + game->player.dir_x * move_speed;
		new_y = game->player.y + game->player.dir_y * move_speed;
		if (game->map->map[(int)new_y][(int)(game->player.x)] != '1')
			game->player.y = new_y;
		if (game->map->map[(int)(game->player.y)][(int)new_x] != '1')
			game->player.x = new_x;
	}

	// Move Backward
	if (keycode == 's' || keycode == 65364)
	{
		new_x = game->player.x - game->player.dir_x * move_speed;
		new_y = game->player.y - game->player.dir_y * move_speed;
		if (game->map->map[(int)new_y][(int)(game->player.x)] != '1')
			game->player.y = new_y;
		if (game->map->map[(int)(game->player.y)][(int)new_x] != '1')
			game->player.x = new_x;
	}

	// Rotate Right
	if (keycode == 'd' || keycode == 65363)
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot_speed)
			- game->player.dir_y * sin(-rot_speed);
		game->player.dir_y = old_dir_x * sin(-rot_speed)
			+ game->player.dir_y * cos(-rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot_speed)
			- game->player.plane_y * sin(-rot_speed);
		game->player.plane_y = old_plane_x * sin(-rot_speed)
			+ game->player.plane_y * cos(-rot_speed);
	}

	// Rotate Left
	if (keycode == 'a' || keycode == 65361)
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot_speed)
			- game->player.dir_y * sin(rot_speed);
		game->player.dir_y = old_dir_x * sin(rot_speed)
			+ game->player.dir_y * cos(rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot_speed)
			- game->player.plane_y * sin(rot_speed);
		game->player.plane_y = old_plane_x * sin(rot_speed)
			+ game->player.plane_y * cos(rot_speed);
	}

	// Refresh scene
	raycast(game);
	render_minimap(game);
	return (0);
}
