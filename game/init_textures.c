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
    game->wall_textures[0] = load_texture(game, "textures/wall_n.xpm"); // North
    game->wall_textures[1] = load_texture(game, "textures/wall_s.xpm"); // South
    game->wall_textures[2] = load_texture(game, "textures/wall_e.xpm");  // East
    game->wall_textures[3] = load_texture(game, "textures/wall_w.xpm");  // West

    for (int i = 0; i < 4; i++) {
        if (!game->wall_textures[i]) {
            printf("Error: Failed to load wall texture %d\n", i);
            return (0);
        }
    }
    return (1);
}
