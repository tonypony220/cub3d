dir		=
SRCS	=	main.c map_parser.c resize_map.c color.c put_map.c put_pixel.c put_obj.c textures.c exiting.c sort.c
OBJS	=	${SRCS:.c=.o}
CFLAGS	=	#-Wall -Wextra -Werror #-fsanitize=address
#HEAD	=	${dir}ft_printf.h
CC		=	gcc
RM		=	rm	-f
NAME	=	run
#.c.o: seems this same as below rule
SUBDIRS := $(gnl)

$(SUBDIRS):
		$(MAKE) -C $@

%.o: %.c
		$(CC) -Imlx -Ignl/Makefile ${CFLAGS} -c $< -o ${<:.c=.o} #
		#${CC} ${CFLAGS} 	   -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} $(SUBDIRS)
		$(CC) ${OBJS} -Lmlx -lmlx -Lgnl -lgnl -Llibft -lft -lz -Lz -framework OpenGL -framework AppKit -o $(NAME)
		#$(CC) ${OBJS} -o $(NAME)

#${NAME}:	fclean	${OBJS} ${HEAD}
#		@${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:	${NAME}
clean:
		@${RM} ${OBJS}
fclean: clean
		@${RM}	${NAME}
re:		fclean	all
.PHONY:	re	bonus	all	clean	fclean

