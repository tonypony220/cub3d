dir		=   .

SRCS	=	main.c map_parser.c resize_map.c color.c put_map.c put_pixel.c put_obj.c textures.c exiting.c sort.c \
            dfs.c make_bmp.c casting.c utils.c sprites.c moving.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=    -O2 #-Wall -Wextra -Werror #-fsanitize=address

HEAD	=	cub3d.h

CC		=	gcc

RM		=	rm	-f

NAME	=	cub3D

SUBDIRS := gnl libft mlx

TOPTARGETS := all clean

$(TOPTARGETS): $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@ $(MAKECMDGOALS)

%.o: %.c $(HEAD)
		$(CC) -Imlx -Ignl -Ilibft ${CFLAGS} -c $< -o ${<:.c=.o} #
		#${CC} ${CFLAGS} 	   -c $< -o ${<:.c=.o}

${NAME}: $(SUBDIRS) ${OBJS}
		$(CC) ${OBJS} -Lmlx -lmlx -Lgnl -lgnl -Llibft -lft -lz -framework OpenGL -framework AppKit -o $(NAME)
		#$(CC) ${OBJS} -o $(NAME)

#${NAME}:	fclean	${OBJS} ${HEAD}
#		@${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:	${NAME}

clean: $(SUBDIRS)
		@${RM} ${OBJS}

fclean: clean
		@${RM}	${NAME}

re:		fclean	all

.PHONY:	re	bonus  all	clean fclean $(SUBDIRS) $(TOPTARGETS)

