/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:44:58 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/20 09:35:10 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

void	put_pixel_img(t_game *game, int x, int y, int color)
{
	int	idx;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	idx = y * game->size_line + x * (game->bpp / 8);
	*(unsigned int *)(game->img_data + idx) = color;
}

void	draw_wall_column(t_game *game, int x, t_ray *ray, t_wall_column *col)
{
	int	y;
	int	tex_y;
	int	color;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)col->tex_pos & (col->tex->height - 1);
		col->tex_pos += col->step;
		color = get_texture_pixel(col->tex, col->tex_x, tex_y);
		if (ray->side == 1 && ray->hit_type != 2)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel_img(game, x, y, color);
		y++;
	}
}

void	draw_textured_wall(t_game *game, int x, t_ray *ray)
{
	t_texture		*tex;
	double			wall_x;
	t_wall_column	col;

	tex = get_wall_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	col.tex = tex;
	col.tex_x = (int)(wall_x * (double)tex->width);
	col.step = 1.0 * tex->height / ray->line_height;
	col.tex_pos = ((double)ray->draw_start - (double)SCREEN_HEIGHT / 2.0
			+ (double)ray->line_height / 2.0) * col.step;
	draw_wall_column(game, x, ray, &col);
}

void	cast_single_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray_vars(game, x, &ray);
	calculate_step_and_side_dist(game, &ray);
	perform_dda(game, &ray);
	calculate_wall_distance(game, &ray);
	draw_ceiling_and_floor(game, x, &ray);
	draw_textured_wall(game, x, &ray);
}

void	raycast(t_game *game)
{
	int	x;

	x = RESERVED_WIDTH;
	while (x < SCREEN_WIDTH)
	{
		cast_single_ray(game, x);
		x++;
	}
	draw_hands(game);
}
