/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:44 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/29 17:41:20 by aylaaouf         ###   ########.fr       */
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
