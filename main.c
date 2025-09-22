/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:46:51 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/09/22 04:52:26 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config(t_config *config)
{
	free(config->no);
	free(config->so);
	free(config->we);
	free(config->ea);
	free(config->f);
	free(config->c);
}

void	free_game_resources(t_game *game)
{
	free_config(game->config);
	free(game->map);
	free(game->config);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free(game);
}

int	init_game(int ac, char **av, t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (1);
	ft_memset(*game, 0, sizeof(t_game));
	(*game)->map = malloc(sizeof(t_map));
	(*game)->config = malloc(sizeof(t_config));
	if (!(*game)->map || !(*game)->config)
	{
		free((*game)->map);
		free((*game)->config);
		free(*game);
		return (1);
	}
	ft_memset((*game)->map, 0, sizeof(t_map));
	ft_memset((*game)->config, 0, sizeof(t_config));
	(*game)->prev_mouse_x = SCREEN_WIDTH / 2;
	if (parser(ac, av, *game))
	{
		free_game_resources(*game);
		return (1);
	}
	init_config((*game)->config);
	find_and_init_player(*game);
	return (0);
}

int	init_window_and_image(t_game *game)
{
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
	{
		fprintf(stderr, "Window creation failed\n");
		return (0);
	}
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
	{
		fprintf(stderr, "Image buffer creation failed\n");
		return (0);
	}
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	return (1);
}

int	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		fprintf(stderr, "MLX init failed\n");
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
		printf("Failed to initialize textures\n");
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
