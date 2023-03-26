SRCS	=	get_next_line.c get_next_line_utils.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror

HEAD	=	get_next_line.h

CC		=	gcc

RM		=	rm	-f

NAME	=	libgnl.a

.c.o: 	${HEAD}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${OBJS} ${HEAD}
		ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS} $(NAME)


fclean: clean
	${RM}	${NAME}

re:		fclean	all

.PHONY:	re	bonus	all	clean	fclean 

