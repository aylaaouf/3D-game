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

int game_loop(t_game *game)
{
	double move_speed = 0.1;
	double rot_speed = 0.05;
	double new_x, new_y;

	if (game->keys.w)
	{
		new_x = game->player.x + game->player.dir_x * move_speed;
		new_y = game->player.y + game->player.dir_y * move_speed;
		if (game->map->map[(int)new_y][(int)new_x] != '1') {
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->keys.s)
	{
		new_x = game->player.x - game->player.dir_x * move_speed;
		new_y = game->player.y - game->player.dir_y * move_speed;
		if (game->map->map[(int)new_y][(int)new_x] != '1') {
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->keys.a)
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
		game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
		game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);
	}
	if (game->keys.d)
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot_speed) - game->player.dir_y * sin(-rot_speed);
		game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y * cos(-rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot_speed) - game->player.plane_y * sin(-rot_speed);
		game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y * cos(-rot_speed);
	}

	raycast(game);
	render_minimap(game);
	return (0);
}

int handle_key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 'w' || keycode == 65362)
		game->keys.w = 1;
	if (keycode == 's' || keycode == 65364)
		game->keys.s = 1;
	if (keycode == 'a' || keycode == 65361)
		game->keys.a = 1;
	if (keycode == 'd' || keycode == 65363)
		game->keys.d = 1;
	return (0);
}

int handle_key_release(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 65362)
		game->keys.w = 0;
	if (keycode == 's' || keycode == 65364)
		game->keys.s = 0;
	if (keycode == 'a' || keycode == 65361)
		game->keys.a = 0;
	if (keycode == 'd' || keycode == 65363)
		game->keys.d = 0;
	return (0);
}
int mouse_move(int x, int y, t_game *game)
{
	static int last_x = -1;
	double rot_speed;

	(void)y; // We don't care about y

	if (last_x == -1)
		last_x = x;

	if (x > last_x)
		rot_speed = -0.03; // turn right
	else if (x < last_x)
		rot_speed = 0.03; // turn left
	else
		return (0);

	// Rotate player direction
	double old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);

	// Rotate camera plane
	double old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);

	last_x = x;

	// Redraw
	raycast(game);
	render_minimap(game);
	return (0);
}
