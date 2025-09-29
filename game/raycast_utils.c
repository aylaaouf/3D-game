/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:07:41 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/23 23:14:32 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

void	update_ray_position(t_ray *ray)
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
}

void	perform_dda(t_game *game, t_ray *ray)
{
	char	tile;

	int (hit);
	hit = 0;
	ray->hit_type = 0;
	while (!hit)
	{
		update_ray_position(ray);
		tile = game->map->map[ray->map_y][ray->map_x];
		if (tile == '1')
		{
			hit = 1;
			ray->hit_type = 1;
		}
		else if (tile == 'P' || tile == 'p')
		{
			hit = 1;
			ray->hit_type = 2;
		}
	}
}

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x)
				/ 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y)
				/ 2.0) / ray->dir_y;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	draw_ceiling_and_floor(t_game *game, int x, t_ray *ray)
{
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = (game->ceil.r << 16) | (game->ceil.g << 8) | (game->ceil.b);
	floor_color = (game->floor.r << 16) | (game->floor.g << 8) | (game->floor.b);

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_img(game, x, y, ceil_color);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_img(game, x, y, floor_color);
		y++;
	}
}
