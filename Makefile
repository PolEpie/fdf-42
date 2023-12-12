# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 16:22:42 by sgoffaux          #+#    #+#              #
#    Updated: 2021/07/12 10:55:42 by sgoffaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
LIBFT		=	libft/
GNL			=	get_next_line/
MLX			=	minilibx/
PRINTF		=	printf/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)
PRINTF_A	=	$(addprefix $(PRINTF), libftprintf.a)

CC			=	gcc
INCLUDE 	=	./includes
CFLAGS		=	-Wall -Werror -Wextra -g3 -I$(INCLUDE)
RM			=	rm -f
SRCS		=	fdf.c \
				srcs/windows.c \
				srcs/matrix.c

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."


OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(GNL_A) $(MLX_A) $(PRINTF_A)
				$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(GNL) -lgnl -L$(MLX) -lmlx -L$(PRINTF) -lftprintf  -L$(MLX)lib -lXext -o $(NAME) -lX11 -lGL -lm -lbsd
				@echo "Linked into executable \033[0;32mfdf\033[0m."

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT) all
				@echo "Compiled $(LIBFT_A)."

$(GNL_A):
				@$(MAKE) -s -C $(GNL)
				@echo "Compiled $(GNL_A)."

$(MLX_A):
				@$(MAKE) -s -C $(MLX)
				@echo "Compiled $(MLX_A)."

$(PRINTF_A):
				@$(MAKE) -s -C $(PRINTF)
				@echo "Compiled $(PRINTF_A)."

bonus:			all

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
				@echo "Compiling $<."

localclean:
				@$(RM) $(OBJS)
				@echo "Removed object files."

clean:			localclean
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Clean libft."
				@$(MAKE) clean -s -C $(GNL)
				@echo "Clean gnl."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."
				@$(MAKE) clean -s -C $(PRINTF)
				@echo "Clean printf."

fclean:			localclean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(MAKE) fclean -s -C $(GNL)
				@echo "Full clean gnl."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."
				@$(MAKE) fclean -s -C $(PRINTF)
				@echo "Clean printf."
				@$(RM) $(NAME)
				@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus 