/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:43:37 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/23 23:14:23 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture	*load_texture(t_game *game, char *path)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		free(texture);
		return (NULL);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (texture);
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(int *)pixel);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	mlx_pixel_put(game->mlx, game->win, x, y, color);
}

void	put_pixel_texture(t_game *game, t_texture *texture, t_pixel_texture *px)
{
	int	color;

	if (px->x < 0 || px->y < 0 || px->x >= 1920 || px->y >= 1080)
		return ;
	if (texture)
		color = get_texture_pixel(texture, px->tex_x, px->tex_y);
	else
		color = 0xFFFFFF;
	mlx_pixel_put(game->mlx, game->win, px->x, px->y, color);
}

void	draw_square_texture(t_game *game, int x, int y, t_texture *texture)
{
	int				i;
	int				j;
	t_pixel_texture	px;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			px.x = x + j;
			px.y = y + i;
			if (texture)
			{
				px.tex_x = (j * texture->width) / TILE_SIZE;
				px.tex_y = (i * texture->height) / TILE_SIZE;
				put_pixel_texture(game, texture, &px);
			}
			else
				put_pixel(game, px.x, px.y, 0xFFFFFF);
			j++;
		}
		i++;
	}
}
