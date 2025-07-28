/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 06:21:11 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/28 16:49:15 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int has_cub_extension(char *path)
{
    char *extension;

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

int is_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    return (line[i] == '\n' || line[i] == '\0');
}

char **read_map(char *path)
{
    int(fd), (i), total_lines;
    char *line;
    char **map;
    int map_started;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (NULL);
    }
    total_lines = count_map_lines(path);
    map_started = 0;
    if (total_lines <= 0)
    {
        close(fd);
        return (NULL);
    }
    map = ft_calloc((total_lines + 1), sizeof(char *));
    if (!map)
    {
        ft_putendl_fd("Error: Failed to read map", 2);
        close(fd);
        return (NULL);
    }
    if (total_lines <= 0)
        return (NULL);
    i = 0;
    while ((line = get_next_line(fd)))
    {
        if (!map_started && !(line[0] == '1' || line[0] == ' '))
        {
            free(line);
            continue;
        }
        if (!map_started && (line[0] == '1' || line[0] == ' '))
            map_started = 1;
        if (map_started)
        {
            if (line[0] == '1' || line[0] == ' ')
            {
                char *newline = ft_strrchr(line, '\n');
                if (newline)
                    *newline = '\0';
                map[i++] = line;
            }
            else if (is_empty_line(line))
            {
                ft_putendl_fd("Error: empty line inside the map", 2);
                free(line);
                free_2d(map);
                get_next_line(-1);
                close(fd);
                return (NULL);
            }
        }
    }
    map[i] = NULL;
    close(fd);
    return (map);
}

int parse_identifiers(int fd, t_game *game)
{
    char *line;
    char *newline;
    int flag;

    flag = 0;
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
            break;
        }
        newline = ft_strrchr(line, '\n');
        if (newline)
            *newline = '\0';
        if (!ft_strncmp(line, "NO ", 3))
        {
            flag++;
            if (game->config->no)
                free(game->config->no);
            game->config->no = ft_strdup(line + 3);
        }
        else if (!ft_strncmp(line, "SO ", 3))
        {
            flag++;
            if (game->config->so)
                free(game->config->so);
            game->config->so = ft_strdup(line + 3);
        }
        else if (!ft_strncmp(line, "WE ", 3))
        {
            flag++;
            if (game->config->we)
                free(game->config->we);
            game->config->we = ft_strdup(line + 3);
        }
        else if (!ft_strncmp(line, "EA ", 3))
        {
            flag++;
            if (game->config->ea)
                free(game->config->ea);
            game->config->ea = ft_strdup(line + 3);
        }
        else if (!ft_strncmp(line, "F ", 2))
        {
            flag++;
            if (game->config->f)
                free(game->config->f);
            game->config->f = ft_strdup(line + 2);
        }
        else if (!ft_strncmp(line, "C ", 2))
        {
            flag++;
            if (game->config->c)
                free(game->config->c);
            game->config->c = ft_strdup(line + 2);
        }
        if (flag > 6)
        {
            ft_putendl_fd("Error: duplicate", 2);
            free(line);
            return (1);
        }
        free(line);
    }
    if (!game->config->no || !game->config->so || !game->config->we || !game->config->ea || !game->config->f || !game->config->c)
    {
        ft_putendl_fd("Error: Missing identifier", 2);
        return (1);
    }
    return (0);
}

int parse_rgb(char *str, t_color *color)
{
    int(r), (g), b;
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
    {
        get_next_line(-1);
        return (1);
    }
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

int is_closed(t_game *game)
{
    int i;
    int j;
    char c;

    i = 0;
    game->map->height = ft_strlen_2d(game->map->map);
    while (i < game->map->height)
    {
        j = 0;
        game->map->last_width = ft_strlen(game->map->map[i]);
        while (j < game->map->last_width)
        {
            c = game->map->map[i][j];
            if (c == '0' || is_player_char(c))
            {
                if (i == 0 || j == 0 || i == game->map->height - 1 || j == game->map->last_width - 1)
                {
                    ft_putendl_fd("Error: Map is not closed by walls", 2);
                    return (1);
                }
                if (game->map->map[i - 1][j] == ' ' ||
                    game->map->map[i + 1][j] == ' ' ||
                    game->map->map[i][j - 1] == ' ' ||
                    game->map->map[i][j + 1] == ' ' ||
                    !game->map->map[i - 1][j] ||
                    !game->map->map[i + 1][j] ||
                    !game->map->map[i][j - 1] ||
                    !game->map->map[i][j + 1])
                {
                    ft_putendl_fd("Error: Map is not closed by walls", 2);
                    return (1);
                }
            }
            j++;
        }
        i++;
    }
    return (0);
}

int parse_map(t_game *game)
{
    int i;
    int j;
    int player;

    player = 0;
    i = 0;
    while (game->map->map[i])
    {
        j = 0;
        while (game->map->map[i][j])
        {
            if (!is_valid_char(game->map->map[i][j]))
            {
                ft_putendl_fd("Error: Invalid character in map", 2);
                return (1);
            }
            if (is_player_char(game->map->map[i][j]))
                player++;
            j++;
        }
        i++;
    }
    if (player != 1)
    {
        if (player == 0)
            ft_putendl_fd("Error: No player found in map", 2);
        else
            ft_putendl_fd("Error: Multiple players found in map", 2);
        return (1);
    }
    if (is_closed(game))
        return (1);
    return (0);
}

int parser(int ac, char **av, t_game *game)
{
    int fd;

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
    if (parse_identifiers(fd, game))
        return ((get_next_line(-1)), 1);
    close(fd);
    if (parse_rgb(game->config->f, &game->config->floor))
    {
        ft_putendl_fd("Error: Invalid floor color", 2);
        return (1);
    }
    if (parse_rgb(game->config->c, &game->config->ceil))
    {
        ft_putendl_fd("Error: Invalid ceiling color", 2);
        return (1);
    }
    game->map->map = read_map(av[1]);
    if (!game->map->map)
        return (1);
    if (parse_map(game))
        return (free_2d(game->map->map), 1);
    return (0);
}
