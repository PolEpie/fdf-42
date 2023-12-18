CC		= cc
CFLAGS	= -Wall -Wextra -Werror
DIR		= srcs/
NAME	= libft.a
SRC		= 	./core/ft_isalnum.c \
			./core/ft_isalpha.c \
			./core/ft_isascii.c \
			./core/ft_isdigit.c \
			./core/ft_isprint.c \
			./core/ft_strlen.c \
			./core/ft_memset.c \
			./core/ft_bzero.c \
			./core/ft_memcpy.c \
			./core/ft_memmove.c \
			./core/ft_strlcat.c \
			./core/ft_strlcpy.c \
			./core/ft_toupper.c \
			./core/ft_tolower.c \
			./core/ft_memchr.c \
			./core/ft_strchr.c \
			./core/ft_strrchr.c \
			./core/ft_memcmp.c \
			./core/ft_strncmp.c \
			./core/ft_strnstr.c \
			./core/ft_atoi.c \
			./core/ft_calloc.c \
			./core/ft_strdup.c \
			./core/ft_substr.c \
			./core/ft_strjoin.c \
			./core/ft_strtrim.c \
			./core/ft_split.c \
			./core/ft_itoa.c \
			./core/ft_strmapi.c \
			./core/ft_striteri.c \
			./core/ft_putchar_fd.c \
			./core/ft_putstr_fd.c \
			./core/ft_putendl_fd.c \
			./core/ft_putnbr_fd.c \
			./core/ft_lstnew_bonus.c \
			./core/ft_lstadd_front_bonus.c \
			./core/ft_lstsize_bonus.c \
			./core/ft_lstlast_bonus.c \
			./core/ft_lstadd_back_bonus.c \
			./core/ft_lstdelone_bonus.c \
			./core/ft_lstclear_bonus.c \
			./core/ft_lstiter_bonus.c \
			./core/ft_lstmap_bonus.c
OBJS	= ${SRC:.c=.o}
HEAD	= ./includes/
AR		= ar rcs
RM		= rm -f

CORE	= libft_core.a

all: ${NAME}

.c.o:
		${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

$(CORE): ${OBJS}
		${AR} ${CORE} ${OBJS}

printf: ${CORE}
		make -C ./printf all

gnl: ${CORE}
		make -C ./get_next_line all

${NAME}: ${OBJS} core printf gnl
		ar x ./libft_core.a
		ar x ./printf/libftprintf.a
		ar x ./get_next_line/libgnl.a
		${AR} ${NAME} *.o
		rm -f *.o

so:
		gcc *.o --shared -o libft.so

clean:      
		rm -f ${OBJS} ${CORE} *.o
		make -C ./printf clean
		make -C ./get_next_line clean

fclean: clean
		rm -f ${NAME}
		make -C ./printf fclean
		make -C ./get_next_line fclean

re: fclean all