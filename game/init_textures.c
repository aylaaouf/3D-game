/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:56:34 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/18 11:45:35 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

int	init_textures(t_game *game)
{
	int (i);
	game->wall_textures[0] = load_texture(game, "textures/wall_s.xpm");
	game->wall_textures[1] = load_texture(game, "textures/wall_n.xpm");
	game->wall_textures[2] = load_texture(game, "textures/wall_w.xpm");
	game->wall_textures[3] = load_texture(game, "textures/wall_e.xpm");
	game->door_texture = load_texture(game, "textures/door.xpm");
	game->hands_img = load_texture(game, "textures/hands.xpm");
	i = 0;
	while (i < 4)
	{
		if (!game->wall_textures[i])
			return (printf("Error: Failed to load wall texture %d\n", i), 0);
		i++;
	}
	if (!game->door_texture)
	{
		printf("Error: Failed to load door texture\n");
		return (0);
	}
	if (!game->hands_img)
	{
		printf("Error: Failed to load hands image\n");
		return (0);
	}
	return (1);
}
