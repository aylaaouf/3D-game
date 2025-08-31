/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:46:51 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/08/31 11:12:18 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_config(t_config *config)
{
    free(config->no);
    free(config->so);
    free(config->we);
    free(config->ea);
    free(config->f);
    free(config->c);
}

int main(int ac, char **av)
{
    t_game *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    ft_memset(game, 0, sizeof(t_game));
    game->map = malloc(sizeof(t_map));
    game->config = malloc(sizeof(t_config));
    if (!game->map || !game->config)
        return (1);
    ft_memset(game->map, 0, sizeof(t_map));
    ft_memset(game->config, 0, sizeof(t_config));
	game->prev_mouse_x = SCREEN_WIDTH  / 2;
    if (parser(ac, av, game))
    {
        free_config(game->config);
        free(game->map);
        free(game->config);
        free(game);
        return (1);
    }
	game->config = malloc(sizeof(t_config));
	init_config(game->config);
	find_and_init_player(game);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	if (!init_textures(game))
	{
		printf("Failed to initialize textures\n");
        return (1);
	}
	game->player.dir_x = -1;
    game->player.dir_y = -0;
    game->player.plane_x = 0;
    game->player.plane_y = 0.66;
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_hook(game->win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
    free_config(game->config);
    free(game->map);
    free(game->config);
    free(game);
    return (0);
}
