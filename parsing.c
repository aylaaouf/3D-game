/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 06:21:11 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/23 10:34:39 by aylaaouf         ###   ########.fr       */
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
        exit(1);
    }
    if (total_lines <= 0)
        return (NULL);
    i = 0;
    while ((line = get_next_line(fd)))
    {
        if (line[0] == '1' || line[0] == ' ')
        {
            char *newline = ft_strrchr(line, '\n');
            if (newline)
                *newline = '\0';
            map[i++] = line;
        }
        else
            free(line);
    }
    map[i] = NULL;
    close(fd);
    return (map);
}

void    parse_identifiers(int fd, t_config *cfg)
{
    char *line;
    char *newline;

    while ((line = get_next_line(fd)))
    {
        if (line[0] == '\n')
        {
            free(line);
            continue;
        }
        else if (line[0] == '1' || line[0] == ' ')
        {
            free(line);
            break ;
        }
        newline = ft_strrchr(line, '\n');
        if (newline)
            *newline = '\0';
        if (!ft_strncmp(line, "NO ", 3))
            cfg->no = ft_strdup(line + 3);
        else if (!ft_strncmp(line, "SO ", 3))
            cfg->so = ft_strdup(line + 3);
        else if (!ft_strncmp(line, "WE ", 3))
            cfg->we = ft_strdup(line + 3);
        else if (!ft_strncmp(line, "EA ", 3))
            cfg->ea = ft_strdup(line + 3);
        else if (!ft_strncmp(line, "F ", 2))
            cfg->f = ft_strdup(line + 2);
        else if (!ft_strncmp(line, "C ", 2))
            cfg->c = ft_strdup(line + 2);
        else
        {
            ft_putendl_fd("Error: Unknown identifier", 2);
            free(line);
            exit(1);
        }
        free(line);
    }
    if (!cfg->no || !cfg->so || !cfg->we || !cfg->ea || !cfg->f || !cfg->c)
    {
        ft_putendl_fd("Error: Missing identifier", 2);
        exit(1);
    }
}

int parse_rgb(char *str, t_color *color)
{
    int (r), (g), b;
    char **split_result;
    if (!str || !color)
        return (1);
    split_result = ft_split(str, ',');
    if (!split_result || !split_result[0] || !split_result[1] || !split_result[2] || split_result[3] != NULL)
    {
        if (split_result)
            free_2d(split_result);
        return (1);
    }
    r = ft_atoi(split_result[0]);
    g = ft_atoi(split_result[1]);
    b = ft_atoi(split_result[2]);
    free_2d(split_result);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return 1;
    color->r = r;
    color->g = g;
    color->b = b;
    return (0);
}

int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || is_player_char(c) || c == '\0');
}

int parse_map(char **map)
{
    int i;
    int j;
    int player;

    player = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!is_valid_char(map[i][j]))
                return (1);
            if (is_player_char(map[i][j]))
                player++;
            j++;
        }
        i++;
    }
    if (player != 1)
        return (1);
    return (0);
}

int parser(int ac, char **av)
{
    char **map;
    t_config    config;
    t_color     color;
    int fd;

    ft_memset(&config, 0, sizeof(config));
    ft_memset(&color, 0, sizeof(color));
    if (ac != 2)
    {
        ft_putendl_fd("Error: Usage: ./cub3d <map.cub>", 2);
        return (1);
    }
    if (has_cub_extension(av[1]))
        return (1);
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }
    parse_identifiers(fd, &config);
    close(fd);
    if (parse_rgb(config.f, &config.floor))
    {
        ft_putendl_fd("Error: Invalid floor color", 2);
        return (1);
    }
    if (parse_rgb(config.c, &config.ceil))
    {
        ft_putendl_fd("Error: Invalid ceiling color", 2);
        return (1);
    }
    map = read_map(av[1]);
    if (!map)
    {
        ft_putendl_fd("Error: Failed to read map", 2);
        close(fd);
        return (1);
    }
    if (parse_map(map))
    {
        ft_putendl_fd("Error: Invalid map", 2);
        free_2d(map);
        return (1);
    }
    return (0);
}