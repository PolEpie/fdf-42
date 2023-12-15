CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DIR			= srcs/
NAME		= libftprintf.a
SRC			= 	./src/ft_printf.c \
				./src/ft_uitoa.c \
				./src/conversion_hex.c \
				./src/conversion_hex_2_bonus.c \
				./src/conversion_char.c \
				./src/conversion_number.c \
				./src/conversion_number_2_bonus.c \
				./src/conversion_ptr.c \
				./src/flag_bonus.c \
				./src/flag_2_bonus.c
OBJS		= ${SRC:.c=.o}
HEAD		= ./includes/
AR			= ar rcs
RM			= rm -f
LIBFT_PATH  = ./../

all: ${NAME}

.c.o:
		${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

$(NAME): $(OBJS)
		cp $(LIBFT_PATH)libft_core.a ${NAME}
		$(AR) $(NAME) ${OBJS}

test:
		${CC} -I ${HEAD} $< ${SRC} libft.a
		./a.out

clean:      
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all

bonus: all