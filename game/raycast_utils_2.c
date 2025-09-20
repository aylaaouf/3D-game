/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:09:28 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/20 09:36:48 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_hands_pixel(t_game *game, int x, int y, t_hands_pixel *pixel)
{
	int	color;

	color = get_texture_pixel(game->hands_img, x, y);
	if ((color & 0x00FFFFFF) != 0xFF00FF && (color & 0x00FFFFFF) != 0x000000)
		put_pixel_img(game, pixel->screen_x + x, pixel->screen_y + y, color);
}

void	draw_hands(t_game *game)
{
	int				x;
	int				y;
	double			breath_offset;
	t_hands_pixel	pixel;

	if (!game->hands_img)
		return ;
	pixel.screen_x = (SCREEN_WIDTH - game->hands_img->width) / 2;
	breath_offset = sin(game->hands_anim_frame * 0.2) * 4.0;
	pixel.screen_y = SCREEN_HEIGHT - game->hands_img->height
		+ (int)breath_offset;
	y = 0;
	while (y < game->hands_img->height)
	{
		x = 0;
		while (x < game->hands_img->width)
		{
			draw_hands_pixel(game, x, y, &pixel);
			x++;
		}
		y++;
	}
	game->hands_anim_frame++;
}

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->hit_type == 2)
		return (game->door_texture);
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->wall_textures[2]);
		else
			return (game->wall_textures[3]);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->wall_textures[1]);
		else
			return (game->wall_textures[0]);
	}
}
