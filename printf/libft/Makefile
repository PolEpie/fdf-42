CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= libft.a
SRC		= 	./ft_isalnum.c \
			./ft_isalpha.c \
			./ft_isascii.c \
			./ft_isdigit.c \
			./ft_isprint.c \
			./ft_strlen.c \
			./ft_memset.c \
			./ft_bzero.c \
			./ft_memcpy.c \
			./ft_memmove.c \
			./ft_strlcat.c \
			./ft_strlcpy.c \
			./ft_toupper.c \
			./ft_tolower.c \
			./ft_memchr.c \
			./ft_strchr.c \
			./ft_strrchr.c \
			./ft_memcmp.c \
			./ft_strncmp.c \
			./ft_strnstr.c \
			./ft_atoi.c \
			./ft_calloc.c \
			./ft_strdup.c \
			./ft_substr.c \
			./ft_strjoin.c \
			./ft_strtrim.c \
			./ft_split.c \
			./ft_itoa.c \
			./ft_strmapi.c \
			./ft_striteri.c \
			./ft_putchar_fd.c \
			./ft_putstr_fd.c \
			./ft_putendl_fd.c \
			./ft_putnbr_fd.c
BONUS_SRC =	./ft_lstnew_bonus.c \
			./ft_lstadd_front_bonus.c \
			./ft_lstsize_bonus.c \
			./ft_lstlast_bonus.c \
			./ft_lstadd_back_bonus.c \
			./ft_lstdelone_bonus.c \
			./ft_lstclear_bonus.c \
			./ft_lstiter_bonus.c \
			./ft_lstmap_bonus.c
OBJS	= ${SRC:.c=.o}
B_OBJS	= ${BONUS_SRC:.c=.o}
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
		rm -f ${B_OBJS}

fclean: clean
		rm -f ${NAME}

test:
		${CC} ${CFLAGS} ${MAIN} ${OBJS}
		./a.out

re: fclean all

bonus: all
		${CC} ${CFLAGS} -c -I ${HEAD} ${SRC} ${BONUS_SRC}
		${AR} ${NAME} ${SRC:.c=.o} ${BONUS_SRC:.c=.o}