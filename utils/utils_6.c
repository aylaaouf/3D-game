/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:00:36 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/22 12:03:30 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_wall_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->wall_textures[i])
		{
			if (game->wall_textures[i]->img)
				mlx_destroy_image(game->mlx, game->wall_textures[i]->img);
			free(game->wall_textures[i]);
		}
		i++;
	}
}

void	free_hand_texture(t_game *game)
{
	if (game->hands_img)
	{
		if (game->hands_img->img)
			mlx_destroy_image(game->mlx, game->hands_img->img);
		free(game->hands_img);
	}
}

void	free_door_texture(t_game *game)
{
	if (game->door_texture)
	{
		if (game->door_texture->img)
			mlx_destroy_image(game->mlx, game->door_texture->img);
		free(game->door_texture);
	}
}

void	free_floor_texture(t_game *game)
{
	if (game->floor_texture)
	{
		if (game->floor_texture->img)
			mlx_destroy_image(game->mlx, game->floor_texture->img);
		free(game->floor_texture);
	}
}

void	free_mlx(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
