CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/color_res_parsing.c src/lst_sort.c src/cub_parsing.c src/main.c src/damage.c src/map_error.c src/deal_key.c src/map_parsing.c src/ft_atoi.c src/move_back.c src/ft_isalpha.c src/move_front.c src/ft_isdigit.c src/move_left.c src/ft_lstdelone.c src/move_right.c src/ft_strdup.c src/path_parsing.c src/ft_strjoin.c src/put_sprite.c src/ft_strncmp.c src/raycaster.c src/get_next_line.c src/save_img.c src/get_next_line_utils.c src/sprite_parsing.c src/hud.c src/up_down_loop.c src/img_create.c src/wall_calculate.c src/init.c src/wall_side.c src/texture_init.c
OBJS = ${SRCS:.c=.o}

NAME =	cub3D

LIB =	cub3d.a

LINK = ar rcs

${NAME}:	${OBJS}
			${LINK} ${LIB} ${OBJS}
			ranlib cub3d.a
			${CC} ${CFLAGS} -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework Appkit ${LIB} -o ${NAME}
			rm ${LIB}

all:		${NAME}

bonus:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f a.out

re: 		fclean all

.PHONY: all clean fclean re