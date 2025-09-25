/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:46:51 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/09/23 23:18:23 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window_and_image(t_game *game)
{
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
	{
		ft_putendl_fd("Window creation failed", 2);
		return (0);
	}
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
	{
		ft_putendl_fd("Image buffer creation failed", 2);
		return (0);
	}
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	return (1);
}

int	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putendl_fd("MLX init failed", 2);
		return (0);
	}
	if (!init_window_and_image(game))
		return (0);
	return (1);
}

int	init_all_textures(t_game *game)
{
	if (!init_textures(game))
	{
		ft_putendl_fd("Failed to initialize textures", 2);
		return (0);
	}
	return (1);
}

void	setup_hooks_and_loop(t_game *game)
{
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_hook(game->win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (init_game(ac, av, &game))
		return (1);
	if (!init_graphics(game))
	{
		free_game_resources(game);
		return (1);
	}
	if (!init_all_textures(game))
	{
		free_game_resources(game);
		return (1);
	}
	setup_hooks_and_loop(game);
	free_game_resources(game);
	return (0);
}
