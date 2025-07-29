/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:44 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/29 22:20:48 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	should_skip_line(char *line)
{
	return (line[0] == '\n');
}

int	is_map_line(char *line)
{
	return (line[0] == '1' || line[0] == ' ');
}

int	condition_b(t_game *game, int player)
{
	if (player_error(player))
		return (1);
	if (is_closed(game))
		return (1);
	return (0);
}
