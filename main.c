/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:46:51 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/28 21:59:42 by ayelasef         ###   ########.fr       */
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
    if (parser(ac, av, game))
    {
        free_config(game->config);
        free(game->map);
        free(game->config);
        free(game);
        return (1);
    }
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	render_minimap(game);
	mlx_key_hook(game->win, handle_keypress, game);
    mlx_loop(game->mlx);
    free_config(game->config);
    free(game->map);
    free(game->config);
    free(game);
    return (0);
}
