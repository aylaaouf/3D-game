/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:32:43 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/20 08:49:34 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

void	draw_square_minimap(t_game *game, int x, int y, int color)
{
	int (i), j;
	i = 0;
	while (i < MINIMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_TILE_SIZE)
		{
			put_pixel_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_game *game)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = MINIMAP_OFFSET_X + (int)(game->player.x * MINIMAP_TILE_SIZE);
	py = MINIMAP_OFFSET_Y + (int)(game->player.y * MINIMAP_TILE_SIZE);
	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			put_pixel_img(game, px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

int	get_minimap_tile_color(char tile)
{
	if (tile == '1')
		return (0x888888);
	else if (tile == 'P' || tile == 'p')
		return (0xFFA500);
	else if (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W')
		return (0xCCCCCC);
	return (-1);
}

void	render_minimap(t_game *game)
{
	render_minimap_tiles(game);
	draw_player_minimap_utils(game);
}

int	render_frame(t_game *game)
{
	game_loop(game);
	raycast(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
