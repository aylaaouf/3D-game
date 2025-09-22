/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:32:26 by ayelasef          #+#    #+#             */
/*   Updated: 2025/09/22 11:33:09 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
