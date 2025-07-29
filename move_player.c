/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:55:36 by ayelasef          #+#    #+#             */
/*   Updated: 2025/07/28 22:01:14 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_keypress(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC key
        exit(0);

    if (keycode == 'w' || keycode == 65362) // up
        game->player.y -= MOVE_STEP;
    if (keycode == 's' || keycode == 65364) // down
        game->player.y += MOVE_STEP;
    if (keycode == 'a' || keycode == 65361) // left
        game->player.x -= MOVE_STEP;
    if (keycode == 'd' || keycode == 65363) // right
        game->player.x += MOVE_STEP;
    mlx_clear_window(game->mlx, game->win);
    render_minimap(game);
    return (0);
}

