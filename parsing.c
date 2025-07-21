/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 06:21:11 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/21 10:19:43 by aylaaouf         ###   ########.fr       */
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

int count_map_lines(char *path)
{
    int fd;
    int counter;
    char *line;

    fd = open(path, O_RDONLY);
    counter = 0;
    if (fd < 0)
    {
        perror("open");
        return (1);
    }
    while ((line = get_next_line(fd)))
    {
        if (line[0] == '1' || line[0] == ' ')
            counter++;
        free(line);
    }
    close(fd);
    return (counter);
}

char    **read_map(char *path)
{
    int (fd), (i), total_lines;
    char *line;
    char **map;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (NULL);
    }
    total_lines = count_map_lines(path);
    map = malloc((total_lines + 1) * sizeof(char *));
    if (!map)
    {
        ft_putendl_fd("Error: Failed to read map", 2);
        return (1);
    }
    if (total_lines <= 0)
        return (NULL);
    i = 0;
    while ((line = get_next_line(fd)))
    {
        if (line[0] == '1' || line[0] == ' ')
            map[i++] = line;
        else
            free(line);
    }
    map[i] = NULL;
    close(fd);
    return (map);
}

int parser(int ac, char **av)
{
    char **map;

    if (ac != 2)
    {
        ft_putendl_fd("Error: Usage: ./cub3d <map.cub>", 2);
        return (1);
    }
    if (has_cub_extension(av[1]))
        return (1);
    map = read_map(av[1]);
    // for (int i = 0; map[i]; i++)
	// 	printf("%s", map[i]);
    return (0);
}