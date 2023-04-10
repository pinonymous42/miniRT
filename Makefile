# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2023/04/10 02:03:07 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
OBJ_DIR		:=	./obj
SRC_DIR		:=	./srcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
CFLAGS  	+=  -fsanitize=address -g

HEADERS			:=  ./includes
LIBFT_DIR		:=	./lib/libft
LIBFT			:=	$(LIBFT_DIR)/libft.a
HEADERS			+=	$(LIBFT_DIR)/includes

MLX_DIR		:=	./lib/mlx
LIBMLX		:=	$(MLX_DIR)/libmlx.a
LXFLAGS		:=	-framework OpenGL -framework AppKit
HEADERS		+= $(MLX_DIR)

INCLUDES		:=	$(addprefix -I , $(HEADERS))

SOURCES :=	main.c
# create_map
SRC_FILE := create_map.c \
			set_ambient.c set_camera.c set_color.c set_light.c set_vec.c create_object.c \
			check_color.c check_vec.c
SOURCES += $(addprefix create_map/, $(SRC_FILE))

#util 
SRC_FILE := color_util.c material_util.c mlx_util.c vec_util.c free_util.c
SOURCES += $(addprefix util/, $(SRC_FILE))

SRC_FILE := comb_v2.c get_t_val.c determin_normal_vec.c
#SRC_FILE := comv_v0.c
SOURCES += $(addprefix refactoring_code/, $(SRC_FILE))
OBJECTS	:= $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))
RM := rm -f
#Message
RED		:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
DEFAULT	:= \033[0m
NAME_MSG	:=	"$(GREEN) Compile $(NAME)$(DEFAULT)"
CLEAN_MSG	:=	"$(YELLOW) Delete $(OBJ_DIR)$(DEFAULT)"
FCLEAN_MSG	:=	"$(RED) Delete $(NAME)$(DEFAULT)"

.PHONY: all fclean clean re libft

$(NAME):   $(LIBFT) $(LIBMLX) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(LIBMLX) $(LXFLAGS) $(OBJECTS)
	@echo $(NAME_MSG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(LIBMLX) : 
	@make -C $(MLX_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(CLEAN_MSG)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

fclean:clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(MLX_DIR)
	@$(RM) $(NAME)
	@echo $(FCLEAN_MSG)

re: fclean all

norm:
	norminette -v
	norminette $(SRC_DIR)
	norminette $(LIBFT_DIR)
	norminette $(includes)
