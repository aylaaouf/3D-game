/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:43:37 by ayelasef          #+#    #+#             */
/*   Updated: 2025/08/31 11:05:59 by ayelasef         ###   ########.fr       */
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

void	put_pixel_texture(t_game *game, int x, int y, t_texture *texture,
		int tex_x, int tex_y)
{
	int	color;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	if (texture)
		color = get_texture_pixel(texture, tex_x, tex_y);
	else
		color = 0xFFFFFF;
	mlx_pixel_put(game->mlx, game->win, x, y, color);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	mlx_pixel_put(game->mlx, game->win, x, y, color);
}

void	draw_square_texture(t_game *game, int x, int y, t_texture *texture)
{
	int i, j;
	int tex_x, tex_y;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (texture)
			{
				tex_x = (j * texture->width) / TILE_SIZE;
				tex_y = (i * texture->height) / TILE_SIZE;
				put_pixel_texture(game, x + j, y + i, texture, tex_x, tex_y);
			}
			else
				put_pixel(game, x + j, y + i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}
