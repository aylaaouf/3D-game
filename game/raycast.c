/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:44:58 by ayelasef          #+#    #+#             */
/*   Updated: 2025/07/29 21:59:42 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void put_pixel_img(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;
	int idx = y * game->size_line + x * (game->bpp / 8);
	*(unsigned int *)(game->img_data + idx) = color;
}

static void	init_ray_vars(t_game *game, int x, t_ray *ray)
{
	double camera_x;

	camera_x = 2 * (x - RESERVED_WIDTH) / (double)(SCREEN_WIDTH - RESERVED_WIDTH) - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2.0) / ray->dir_y;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

static void	draw_ceiling_and_floor(t_game *game, int x, t_ray *ray)
{
	int y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_img(game, x, y, 0x87CEEB);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_img(game, x, y, 0xFFFFFF);
		y++;
	}
}

static t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
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

static void	draw_textured_wall(t_game *game, int x, t_ray *ray)
{
	t_texture	*tex;
	double		wall_x;
	double		step;
	double		tex_pos;

	int (y), tex_y, color, tex_x;
	tex = get_wall_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (double)(ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_texture_pixel(tex, tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel_img(game, x, y, color);
		y++;
	}
}

static void	cast_single_ray(t_game *game, int x)
{
	t_ray ray;

	init_ray_vars(game, x, &ray);
	calculate_step_and_side_dist(game, &ray);
	perform_dda(game, &ray);
	calculate_wall_distance(game, &ray);
	draw_ceiling_and_floor(game, x, &ray);
	draw_textured_wall(game, x, &ray);
}

void	raycast(t_game *game)
{
	int x;

	x = RESERVED_WIDTH;
	while (x < SCREEN_WIDTH)
	{
		cast_single_ray(game, x);
		x++;
	}
}
