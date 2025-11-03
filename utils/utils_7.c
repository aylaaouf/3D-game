/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:12:35 by ayelasef          #+#    #+#             */
/*   Updated: 2025/11/03 18:13:42 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_game	*allocate_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->map = malloc(sizeof(t_map));
	game->config = malloc(sizeof(t_config));
	if (!game->map || !game->config)
	{
		free(game->map);
		free(game->config);
		free(game);
		return (NULL);
	}
	ft_memset(game->map, 0, sizeof(t_map));
	ft_memset(game->config, 0, sizeof(t_config));
	init_config(game->config);
	game->prev_mouse_x = SCREEN_WIDTH / 2;
	return (game);
}
