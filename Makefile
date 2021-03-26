dir		=   .

SRCS	=	main.c map_parser.c color.c put_pixel.c put_obj.c textures.c exiting.c sort.c \
            dfs.c make_bmp.c casting.c utils.c sprites.c moving.c hooks.c parsing.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=    -O0 -Wall -Wextra -Werror -g #-fsanitize=address

HEAD	=	cub3d.h

CC		=	gcc

RM		=	-rm	-f

NAME	=	cub3D

SUBDIRS := gnl libft mlx

TOPTARGETS := all clean fclean

$(TOPTARGETS): $(SUBDIRS)

$(libs): $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@ $(MAKECMDGOALS)

%.o: %.c $(HEAD)
		$(CC) -Imlx -Ignl -Ilibft ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		$(CC) ${OBJS} -Lmlx -lmlx -Lgnl -lgnl -Llibft -lft -lz -framework OpenGL -framework AppKit -o ${NAME}

all:	${NAME}

clean: $(SUBDIRS)
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:     fclean	all

.PHONY:	re bonus all clean fclean $(SUBDIRS) $(TOPTARGETS)
