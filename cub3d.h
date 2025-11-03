/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:53:14 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/11/03 17:10:32 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define USAGE_ERR "Error\nUsage — correct format is ./cub3d <map.cub>"
# define INVALID_FLOOR "Error\nInvalid floor RGB color format"
# define INVALID_CEILING "Error\nInvalid ceiling RGB color format"
# define MAP_NOT_CLOSED "Error\nMap is not properly enclosed by walls"
# define NO_PLAYER_FOUND "Error\nPlayer starting position is missing in the map"
# define MULTI_PLAYERS "Error\nMultiple player positions found in the map"
# define INVALID_PATH "Error\nInvalid map path or unreachable area"
# define INVALID_EXT "Error\nFile extension must be .cub"
# define EMPTY_MAP_LINE "Error\nEmpty line found inside the map data"
# define MAP_READ_FAIL "Error\nFailed to read the map file"
# define DUPLICATE_ID "Error\nDuplicate identifier found"
# define MISSING_ID "Error\nOne or more required identifiers are missing"
# define INVALID_CHAR_MAP "Error\nInvalid character detected in the map"

# define MOVE_STEP 0.1
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define TILE_SIZE 8 // minimap tile size in pixels
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# define MINIMAP_TILE_SIZE 8
# define MINIMAP_WIDTH 10  // tiles
# define MINIMAP_HEIGHT 10 // tiles
# define RESERVED_WIDTH 0

typedef struct s_map
{
	char		**map;
	int			height;
	int			last_width;
}				t_map;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_texture
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_config
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	t_color		floor;
	t_color		ceil;
}				t_config;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
}				t_keys;

typedef struct s_img
{
	void		*mlx_img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_game
{
	t_map		*map;
	t_config	*config;
	t_player	player;
	void		*mlx;
	void		*win;
	double		ray_dir_x;
	double		ray_dir_y;
	int			prev_px;
	int			prev_py;
	int			prev_mouse_x;
	int			hands_anim_frame;
	t_keys		keys;
	t_texture	*hands_img;
	t_texture	*wall_textures[4];
	t_texture	*door_texture;
	t_texture	*floor_texture;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_img		*img;
	t_color		floor;
	t_color		ceil;
}				t_game;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			hit_type;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_wall_column
{
	t_texture	*tex;
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_wall_column;

typedef struct s_hands_pixel
{
	int			screen_x;
	int			screen_y;
}				t_hands_pixel;

typedef struct s_tile_move
{
	double		*coord;
	double		move;
	double		step;
	int			map_index;
}				t_tile_move;
typedef struct s_pixel_texture
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;
}				t_pixel_texture;
// init
int				rgb(int r, int g, int b);
void			init_color(t_color *color, int r, int g, int b);
int				find_and_init_player(t_game *game);
void			init_player(t_player *player, int x, int y, char dir);
void			init_config(t_config *config);
// parsing
int				parser(int ac, char **av, t_game *game);
int				has_cub_extension(char *path);
int				count_map_lines(char *path);
int				is_empty_line(char *line);
int				is_player_char(char c);
int				is_valid_char(char c);
int				check_door_condition(t_game *g, int i, int j);
char			**read_map(char *path);
int				is_closed(t_game *game);
int				ft_isdegit(char *str);
int				parse_identifiers(int fd, t_game *game);
int				player_error(int player);
int				should_skip_line(char *line);
int				is_map_line(char *line);
int				condition_b(t_game *game, int player);
int				close_game(t_game *game);

// utils
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen_2d(char **args);
size_t			ft_strlen(const char *s);
void			ft_putendl_fd(char *s, int fd);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strdup(const char *s1);
void			*ft_memcpy(void *dst, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
void			free_2d(char **args);
void			*ft_calloc(size_t count, size_t size);
void			free_config(t_config *config);
void			free_game_resources(t_game *game);
int				init_game(int ac, char **av, t_game **game);
void			free_wall_textures(t_game *game);
void			free_hand_texture(t_game *game);
void			free_door_texture(t_game *game);
void			free_floor_texture(t_game *game);
void			free_mlx(t_game *game);
// raycast
void			put_pixel_img(t_game *game, int x, int y, int color);

void			raycast(t_game *game);

// raycast_utils
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_step_and_side_dist(t_game *game, t_ray *ray);
void			init_ray_vars(t_game *game, int x, t_ray *ray);
void			draw_ceiling_and_floor(t_game *game, int x, t_ray *ray);
void			calculate_wall_distance(t_game *game, t_ray *ray);
void			draw_hands(t_game *game);
t_texture		*get_wall_texture(t_game *game, t_ray *ray);
// minimap

int				get_minimap_tile_color(char tile);
void			draw_square_minimap(t_game *game, int x, int y, int color);
void			draw_square(t_game *game, int x, int y, int color);
int				render_frame(t_game *game);
void			render_minimap(t_game *game);
void			draw_square_texture(t_game *game, int x, int y,
					t_texture *texture);
// minimap_utils

void			draw_player_minimap_utils(t_game *game);
void			render_minimap_tiles(t_game *game);
// move_player

void			move_through_tile(t_game *game, double *coord, double move,
					int axis);
int				handle_key_release(int keycode, t_game *game);
int				handle_key_press(int keycode, t_game *game);
int				game_loop(t_game *game);
int				mouse_move(int x, int y, t_game *game);
int				handle_keypress(int keycode, t_game *game);
// move_player_utils

void			move_through_tile_y(t_game *game, t_tile_move *move_info);
void			move_through_tile_x(t_game *game, t_tile_move *move_info);

void			apply_rotation(t_game *game, double angle);
void			handle_move_keys(t_game *game, double *new_x, double *new_y,
					double move_speed);
void			handle_rotate_right(t_game *game, double rot_speed);
void			handle_rotate_left(t_game *game, double rot_speed);
// inir_textures

int				init_textures(t_game *game);
// texture_rendering

t_texture		*load_texture(t_game *game, char *path);
int				get_texture_pixel(t_texture *texture, int x, int y);
void			put_pixel(t_game *game, int x, int y, int color);
#endif
