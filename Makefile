CC = gcc
CFLAGS = -Wall -Wextra -Werror -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework Appkit

SRCS = src/*.c
OBJS = ${SRCS:.c=.o}

NAME =	Cub3D

${NAME}:	
			${CC} ${CFLAGS} ${SRCS} -o ${NAME}

all:		${NAME}

bonus:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f a.out

re: 		fclean all

.PHONY: all clean fclean re