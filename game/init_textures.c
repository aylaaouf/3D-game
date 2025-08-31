/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:56:34 by ayelasef          #+#    #+#             */
/*   Updated: 2025/08/31 11:07:51 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int init_textures(t_game *game)
{
    game->wall_texture = load_texture(game, "textures/wall.xpm");
    game->floor_texture = load_texture(game, "textures/floor.xpm");
    
    if (!game->wall_texture)
    {
        printf("Error: Failed to load wall texture\n");
        return (0);
    }
    return (1);
}
