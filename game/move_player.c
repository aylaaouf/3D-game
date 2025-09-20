/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:55:36 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/18 11:45:58 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_through_tile(t_game *game, double *coord, double move, int axis)
{
	int		map_x;
	int		map_y;
	char	cell;
	double	step;
	double	target;

	step = 0.2;
	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	target = *coord + move;
	if (axis == 0)
	{
		cell = game->map->map[(int)target][map_x];
		if (cell == '0')
			*coord = target;
		else if (cell == 'P')
		{
			while (cell == 'P')
			{
				target += (move > 0) ? step : -step;
				cell = game->map->map[(int)target][map_x];
			}
			if (cell == '0')
				*coord = target;
		}
	}
	else if (axis == 1)
	{
		cell = game->map->map[map_y][(int)target];
		if (cell == '0')
			*coord = target;
		else if (cell == 'P')
		{
			while (cell == 'P')
			{
				target += (move > 0) ? step : -step;
				cell = game->map->map[map_y][(int)target];
			}
			if (cell == '0')
				*coord = target;
		}
	}
}

int	game_loop(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	old_dir_x;
	double	old_plane_x;

	move_speed = 0.09;
	rot_speed = 0.05;
	new_x = game->player.x;
	new_y = game->player.y;
	if (game->keys.w)
	{
		move_through_tile(game, &new_y, game->player.dir_y * move_speed, 0);
		move_through_tile(game, &new_x, game->player.dir_x * move_speed, 1);
	}
	if (game->keys.s)
	{
		move_through_tile(game, &new_y, -game->player.dir_y * move_speed, 0);
		move_through_tile(game, &new_x, -game->player.dir_x * move_speed, 1);
	}
	game->player.x = new_x;
	game->player.y = new_y;
	if (game->keys.d)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot_speed)
			- game->player.dir_y * sin(rot_speed);
		game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
			* cos(rot_speed);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot_speed)
			- game->player.plane_y * sin(rot_speed);
		game->player.plane_y = old_plane_x * sin(rot_speed)
			+ game->player.plane_y * cos(rot_speed);
	}
	if (game->keys.a)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot_speed)
			- game->player.dir_y * sin(-rot_speed);
		game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y
			* cos(-rot_speed);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot_speed)
			- game->player.plane_y * sin(-rot_speed);
		game->player.plane_y = old_plane_x * sin(-rot_speed)
			+ game->player.plane_y * cos(-rot_speed);
	}
	return (0);
}

int	handle_key_press(int keycode, t_game *game)
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

int	handle_key_release(int keycode, t_game *game)
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

int	mouse_move(int x, int y, t_game *game)
{
	double	sensitivity;
	int		delta_x;
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	(void)y;
	sensitivity = 0.0009;
	delta_x = x - game->prev_mouse_x;
	if (delta_x != 0)
	{
		angle = delta_x * sensitivity;
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(angle)
			- game->player.dir_y * sin(angle);
		game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
			* cos(angle);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(angle)
			- game->player.plane_y * sin(angle);
		game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
			* cos(angle);
		mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT
			/ 2);
		game->prev_mouse_x = SCREEN_WIDTH / 2;
	}
	return (0);
}
