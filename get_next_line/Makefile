CC		= cc
CFLAGS	= -Wall -Wextra -Werror
DIR		= srcs/
NAME	= libgnl.a
SRC		= 	./get_next_line.c \
			./get_next_line_utils.c
OBJS	= ${SRC:.c=.o}
HEAD	= ./includes/
AR		= ar rcs
RM		= rm -f

all: ${NAME}

.c.o:
		${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		${AR} ${NAME} ${OBJS}

so:
		gcc *.o --shared -o libft.so

clean:      
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

test: all
		${CC} ${CFLAGS} ${MAIN} ${OBJS}
		./a.out

re: fclean all

bonus:
		${CC} ${CFLAGS} -c -I ${HEAD} ${SRC} ${BONUS_SRC}
		${AR} ${NAME} ${SRC:.c=.o} ${BONUS_SRC:.c=.o}