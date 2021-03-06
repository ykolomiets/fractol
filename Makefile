# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 16:54:48 by ykolomie          #+#    #+#              #
#    Updated: 2017/10/10 13:07:38 by ykolomie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_DIR =        ./srcs/
OBJ_DIR =        ./obj/
LIBFT_DIR =      ./libft
LIBMATHX_DIR =   ./math_extended
LIBMLX_DIR =     ./minilibx_macos
FDF_DIR =		 ./fdf

LIBFT =         libft.a
LIBMATHX =      libmathx.a
LIBMLX =        libmlx.a
FDF = 			fdf

SRC_FILES = 	main.c				\
                fractol.c           \
				palettes.c          \
				render.c            \
				sets.c				\
				hooks.c             \
				fractol_fdf.c

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC = -I ./includes -I $(LIBFT_DIR) -I $(LIBMLX_DIR) -I $(LIBMATHX_DIR)

LIBFLAGS = -lft -L $(LIBFT_DIR) -lmlx -L $(LIBMLX_DIR) -L $(LIBMATHX_DIR) -lmathx -lm

FRAMEWORKS = -framework OpenGL -framework AppKit

FLAGS = -Werror -Wextra -Wall

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/$(LIBFT) $(LIBMATHX_DIR)/$(LIBMATHX) $(LIBMLX_DIR)/$(LIBMLX) $(FDF_DIR)/$(FDF)
	     $(CC) $(OBJ) $(FLAGS) $(FRAMEWORKS) $(LIBFLAGS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@  

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT_DIR)/$(LIBFT):
	make -s -C $(LIBFT_DIR)/

$(LIBMATHX_DIR)/$(LIBMATHX):
	make -s -C $(LIBMATHX_DIR)/
	
$(LIBMLX_DIR)/$(LIBMLX):
	make -s -C $(LIBMLX_DIR)/

$(FDF_DIR)/$(FDF):
	make -s -C $(FDF_DIR)/
	
clean: libclean
	rm -rf $(OBJ)

fclean: clean libfclean
	rm -rf $(NAME)

libclean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBMATHX_DIR)
	make clean -C $(LIBMLX_DIR)
	make clean -C $(FDF_DIR)

libfclean:
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBMATHX_DIR)
	make clean  -C $(LIBMLX_DIR)
	make clean  -C $(FDF_DIR)

re: fclean libfclean all
