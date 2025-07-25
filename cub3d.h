/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:53:14 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/25 16:00:16 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include <string.h>
# include <unistd.h>
# include "gnl/get_next_line.h"
# include <fcntl.h>

typedef struct s_map
{
    char **map;
    int height;
    int last_width;
}              t_map;

typedef struct s_color {
    int r;
    int g;
    int b;
}              t_color;

typedef struct s_config {
    char *no;
    char *so;
    char *we;
    char *ea;
    char *f;
    char *c;
    t_color floor;
    t_color ceil;
}              t_config;

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_game
{
    t_map     *map;
    t_config  *config;
    t_player  player;
    void      *mlx;
    void      *win;
} t_game;

// parsing
int     parser(int ac, char **av, t_game *game);
int     has_cub_extension(char *path);

// utils
char	*ft_strrchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strlen_2d(char **args);
size_t  ft_strlen(const char *s);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int	    ft_atoi(const char *str);
void	free_2d(char **args);

#endif