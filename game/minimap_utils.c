/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 08:47:47 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/20 08:51:27 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_minimap_tiles(t_game *game)
{
	char	tile;

	int (width), color, (map_y), map_x;
	map_y = 0;
	while (map_y < game->map->height)
	{
		width = ft_strlen(game->map->map[map_y]);
		map_x = 0;
		while (map_x < width)
		{
			tile = game->map->map[map_y][map_x];
			color = get_minimap_tile_color(tile);
			if (color == -1)
			{
				map_x++;
				continue ;
			}
			draw_square_minimap(game, MINIMAP_OFFSET_X + map_x
				* MINIMAP_TILE_SIZE, MINIMAP_OFFSET_Y + map_y
				* MINIMAP_TILE_SIZE, color);
			map_x++;
		}
		map_y++;
	}
}

void	draw_player_minimap_utils(t_game *game)
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
