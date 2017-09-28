# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 16:54:48 by ykolomie          #+#    #+#              #
#    Updated: 2017/04/20 15:27:53 by ykolomie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_DIR =        ./srcs/
OBJ_DIR =        ./obj/
LIBFT_DIR =      ./libft
LIBMATHX_DIR =   ./math_extended
LIBMLX_DIR =     ./minilibx_macos

LIBFT =         libft.a
LIBMATHX =      libmathx.a
LIBMLX =        libmlx.a

SRC_FILES = 	main.c				\
                fractol.c           \
				rgb.c               \
				hsv.c               \
				palletes.c          \
				render.c            \
				sets.c

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC = -I ./includes -I $(LIBFT_DIR) -I $(LIBMLX_DIR) -I $(LIBMATHX_DIR)

LIBFLAGS = -lft -L $(LIBFT_DIR) -lmlx -L $(LIBMLX_DIR) -L $(LIBMATHX_DIR) -lmathx -lm

FRAMEWORKS = -framework OpenGL -framework AppKit

FLAGS = -Werror -Wextra -Wall

CC = clang

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/$(LIBFT) $(LIBMATHX_DIR)/$(LIBMATHX) $(LIBMLX_DIR)/$(LIBMLX)
	     $(CC) $(OBJ) $(FLAGS) $(FRAMEWORKS) $(LIBFLAGS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c ./includes/*.h
	$(CC) $(FLAGS) $(INC) -c $< -o $@  

$(LIBFT_DIR)/$(LIBFT):
	make -s -C $(LIBFT_DIR)/

$(LIBMATHX_DIR)/$(LIBMATHX):
	make -s -C $(LIBMATHX_DIR)/
	
$(LIBMLX_DIR)/$(LIBMLX):
	make -s -C $(LIBMLX_DIR)/
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

libclean:
	make clean -C $(LIBFTFOLDER)

libfclean:
	make fclean -C $(LIBFTFOLDER)

re: fclean libfclean all
