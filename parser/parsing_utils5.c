/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:08:59 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/11/03 19:21:19 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	validate_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd(OPEN_ERR, 2);
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_texture_identifiers(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (set_identifier(&game->config->no, line, 3, 1));
	else if (!ft_strncmp(line, "SO ", 3))
		return (set_identifier(&game->config->so, line, 3, 1));
	else if (!ft_strncmp(line, "WE ", 3))
		return (set_identifier(&game->config->we, line, 3, 1));
	else if (!ft_strncmp(line, "EA ", 3))
		return (set_identifier(&game->config->ea, line, 3, 1));
	return (-1);
}

int	handle_color_identifiers(char *line, t_game *game)
{
	if (!ft_strncmp(line, "F ", 2))
		return (set_identifier(&game->config->f, line, 2, 0));
	else if (!ft_strncmp(line, "C ", 2))
		return (set_identifier(&game->config->c, line, 2, 0));
	return (-1);
}
