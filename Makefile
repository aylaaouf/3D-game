NAME := cub3d

SRC:= main.c parser/parsing.c parser/parsing_utils.c parser/parsing_utils2.c \
		parser/parsing_utils3.c parser/parsing_utils4.c utils/utils.c utils/utils_2.c \
		utils/utils_3.c utils/utils_4.c gnl/get_next_line.c gnl/get_next_line_utils.c \

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
