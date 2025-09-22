/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:55:36 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/22 11:45:21 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_through_tile(t_game *game, double *coord, double move, int axis)
{
	int			map_x;
	int			map_y;
	double		step;
	t_tile_move	move_info;

	step = 0.2;
	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	move_info.coord = coord;
	move_info.move = move;
	move_info.step = step;
	if (axis == 0)
	{
		move_info.map_index = map_x;
		move_through_tile_x(game, &move_info);
	}
	else if (axis == 1)
	{
		move_info.map_index = map_y;
		move_through_tile_y(game, &move_info);
	}
}

int	game_loop(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.09;
	rot_speed = 0.05;
	new_x = game->player.x;
	new_y = game->player.y;
	handle_move_keys(game, &new_x, &new_y, move_speed);
	game->player.x = new_x;
	game->player.y = new_y;
	if (game->keys.d)
		handle_rotate_right(game, rot_speed);
	if (game->keys.a)
		handle_rotate_left(game, rot_speed);
	return (0);
}

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		free_game_resources(game);
		exit(0);
	}
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
	double	angle;
	int		delta_x;

	(void)y;
	sensitivity = 0.0009;
	delta_x = x - game->prev_mouse_x;
	if (delta_x != 0)
	{
		angle = delta_x * sensitivity;
		apply_rotation(game, angle);
		mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT
			/ 2);
		game->prev_mouse_x = SCREEN_WIDTH / 2;
	}
	return (0);
}
