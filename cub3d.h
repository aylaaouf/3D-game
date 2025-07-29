/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:53:14 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/29 22:22:23 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>

#define WALL_ERR "Error: Map is not closed by walls"
#define MOVE_STEP 0.2
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define TILE_SIZE 8       // minimap tile size in pixels
#define MINIMAP_OFFSET_X 20
#define MINIMAP_OFFSET_Y 20
#define MINIMAP_WIDTH 10  // tiles
#define MINIMAP_HEIGHT 10 // tiles
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
	int         prev_px;
    int         prev_py;
} t_game;

//init
int	rgb(int r, int g, int b);
void init_color(t_color *color, int r, int g, int b);
void	find_and_init_player(t_game *game);
void init_player(t_player *player, int x, int y, char dir);
void init_config(t_config *config);
// parsing
int     parser(int ac, char **av, t_game *game);
int     has_cub_extension(char *path);
int	    count_map_lines(char *path);
int	    is_empty_line(char *line);
int	    is_player_char(char c);
int     is_valid_char(char c);
char	**read_map(char *path);
int     is_closed(t_game *game);
int	    parse_identifiers(int fd, t_game *game);
int     player_error(int player);
int     should_skip_line(char *line);
int     is_map_line(char *line);
int     condition_b(t_game *game, int player);

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
void	*ft_calloc(size_t count, size_t size);
//raycast

void	raycast(t_game *game);
//minimap

void draw_square(t_game *game, int x, int y, int color);
int render_frame(t_game *game);
void	render_minimap(t_game *game);
//move_player 

int handle_keypress(int keycode, t_game *game);
#endif
