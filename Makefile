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
MLX			=	minilibx/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

CC			=	gcc
INCLUDE 	=	./includes/
CFLAGS		=	-Wall -Werror -Wextra -g -I$(INCLUDE) -I$(LIBFT)includes
RM			=	rm -f
OBJ_DIR		=	objs
SRCS		=	fdf.c \
				srcs/windows.c \
				srcs/windows_mouse.c \
				srcs/windows_keybinds.c \
				srcs/draw.c \
				srcs/camera.c \
				srcs/parser.c \
				srcs/utils.c \
				srcs/matrix.c


X11_FLAGS = -L/usr/X11/lib -lXext -lX11 -framework Cocoa -framework OpenGL -framework AppKit


OBJS		=	$(SRCS:/%.c=%.o)

OS_NAME		:=	$(shell uname -s | tr A-Z a-z)

$(NAME):		$(OBJS) $(LIBFT_A) $(MLX_A)
				@if [ "$(OS_NAME)" = "darwin" ]; then \
					echo "Compiling for MacOS..."; \
					$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(MLX) -lmlx -o $(NAME) $(MACOS_FLAG); \
				else \
					echo "Compiling for Linux..."; \
					$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -o $(NAME) $(LINUX_FLAG); \
				fi
				@echo "Linked into executable \033[0;32mfdf\033[0m."

all:			test

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

MACOS_FLAG	=	-L/usr/X11/lib -lX11 -lXext
LINUX_FLAG	=	-L$(MLX) -lmlx -L$(MLX)lib -lX11 -lXext -lGL -lm -lbsd

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT) all
				@echo "Compiled $(LIBFT_A)."

$(MLX_A):
				@$(MAKE) -s -C $(MLX)
				@echo "Compiled $(MLX_A)."

bonus:			all

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$(<:.c=.o)
				@echo "Compiling $<."

localclean:
				@$(RM) -rf $(OBJ_DIR)
				@mkdir $(OBJ_DIR)
				@echo "Removed object files."

clean:			localclean
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Clean libft."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."

fclean:			localclean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."
				@$(RM) $(NAME)
				@echo "Removed executable."

test:			$(NAME)
				./fdf test_maps/42.fdf 

re:				fclean all

.PHONY:			all clean fclean re localclean bonus 