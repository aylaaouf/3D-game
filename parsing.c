/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 06:21:11 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/21 08:46:19 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int has_cub_extension(char *path)
{
    char    *extension;

    extension = ft_strrchr(path, '.');
    if (extension == NULL)
    {
        ft_putendl_fd("Error: Not a valid path", 2);
        return (1);
    }
    if (strcmp(extension, ".cub") == 0)
        return (0);
    else
    {
        ft_putendl_fd("Error: Not a valid extension", 2);
        return (1);
    }
}

int parser(int ac, char **av)
{
    if (ac != 2)
    {
        ft_putendl_fd("Error: Usage: ./cub3d <map.cub>", 2);
        return (1);
    }
    if (has_cub_extension(av[1]))
        return (1);
    read_map(av[1]);
    return (0);
}