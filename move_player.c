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
	int	screen_x, screen_y, py, px;
    screen_x = game->player.x * TILE_SIZE;
    screen_y = game->player.y * TILE_SIZE;
	py = 0;
    while (py < 4)
	{
		px = 0;
        while (px < 4)
		{
			mlx_pixel_put(game->mlx, game->win, screen_x + px, 
			   screen_y + py, 0xFF0000);
			px++;
		}
		py++;
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	double move_speed = 0.1;
	double new_x = game->player.x;
	double new_y = game->player.y;

	if (keycode == 65307)
		exit(0);

	if (keycode == 'w' || keycode == 65362)
	{
		new_x += game->player.dir_x * move_speed;
		new_y += game->player.dir_y * move_speed;
	}
	if (keycode == 's' || keycode == 65364)
	{
		new_x -= game->player.dir_x * move_speed;
		new_y -= game->player.dir_y * move_speed;
	}
	if (keycode == 'a' || keycode == 65361)
	{
		new_x -= game->player.plane_x * move_speed;
		new_y -= game->player.plane_y * move_speed;
	}
	if (keycode == 'd' || keycode == 65363)
	{
		new_x += game->player.plane_x * move_speed;
		new_y += game->player.plane_y * move_speed;
	}
	if (game->map->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	raycast(game);
	render_minimap(game);
	return (0);
}
