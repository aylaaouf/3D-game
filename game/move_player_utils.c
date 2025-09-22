/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 03:03:09 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/22 03:08:50 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_through_tile_x(t_game *game, t_tile_move *move_info)
{
	char	cell;
	double	target;

	target = *(move_info->coord) + move_info->move;
	cell = game->map->map[(int)target][move_info->map_index];
	if (cell == '0')
		*(move_info->coord) = target;
	else if (cell == 'P')
	{
		while (cell == 'P')
		{
			if (move_info->move > 0)
				target += move_info->step;
			else
				target -= move_info->step;
			cell = game->map->map[(int)target][move_info->map_index];
		}
		if (cell == '0')
			*(move_info->coord) = target;
	}
}

void	move_through_tile_y(t_game *game, t_tile_move *move_info)
{
	char	cell;
	double	target;

	target = *(move_info->coord) + move_info->move;
	cell = game->map->map[move_info->map_index][(int)target];
	if (cell == '0')
		*(move_info->coord) = target;
	else if (cell == 'P')
	{
		while (cell == 'P')
		{
			if (move_info->move > 0)
				target += move_info->step;
			else
				target -= move_info->step;
			cell = game->map->map[move_info->map_index][(int)target];
		}
		if (cell == '0')
			*(move_info->coord) = target;
	}
}

void	handle_move_keys(t_game *game, double *new_x, double *new_y,
		double move_speed)
{
	if (game->keys.w)
	{
		move_through_tile(game, new_y, game->player.dir_y * move_speed, 0);
		move_through_tile(game, new_x, game->player.dir_x * move_speed, 1);
	}
	if (game->keys.s)
	{
		move_through_tile(game, new_y, -game->player.dir_y * move_speed, 0);
		move_through_tile(game, new_x, -game->player.dir_x * move_speed, 1);
	}
}

void	handle_rotate_right(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
}

void	handle_rotate_left(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot_speed)
		- game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y
		* cos(-rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot_speed)
		- game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y
		* cos(-rot_speed);
}
