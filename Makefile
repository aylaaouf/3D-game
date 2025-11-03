NAME := cub3d

SRC:= main.c parser/parsing.c parser/parsing_utils.c parser/parsing_utils2.c \
		parser/parsing_utils3.c parser/parsing_utils4.c utils/utils.c utils/utils_2.c \
		utils/utils_3.c utils/utils_4.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		game/minimap.c game/move_player.c game/raycast.c game/init.c  game/init_textures.c game/texture_rendering.c \
		game/raycast_utils_2.c game/raycast_utils.c game/minimap_utils.c \
		game/init_2.c game/move_player_utils.c  game/move_player_utils_2.c \
		utils/utils_5.c utils/utils_6.c utils/utils_7.c
CC := cc

CFLAGS := -Wall -Wextra -Werror -I./minilibx-linux

LIBXFLAGS := -L./minilibx-linux -lmlx -lXext -lX11 -lm
OBJS := $(SRC:.c=.o)
all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBXFLAGS) -o $(NAME)

bonus: all

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
