NAME := cub3d

SRC:= main.c parsing.c utils.c utils_2.c gnl/get_next_line.c \
	  gnl/get_next_line_utils.c

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