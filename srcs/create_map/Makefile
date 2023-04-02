# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2023/04/02 13:53:23 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
OBJ_DIR		:=	./obj
SRC_DIR		:=	./
CC			:=	cc
#CFLAGS		:=	-Wall -Werror -Wextra
#CFLAGS  	+=  -fsanitize=address -g

HEADERS			:=  ../../includes
LIBFT_DIR		:=	../../lib/libft
LIBFT			:=	$(LIBFT_DIR)/libft.a
HEADERS			+=	$(LIBFT_DIR)/includes

INCLUDES		:=	$(addprefix -I , $(HEADERS))

SOURCES :=	main.c
SRC_FILE := create_map.c set_ambient.c set_camera.c set_color.c set_light.c set_vec.c create_object.c check_color.c check_vec.c
SRC_FILE += util.c
SRC_FILE += leakdetect.c
SOURCES += $(SRC_FILE)

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

$(NAME):   $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT)  $(OBJECTS)
	@echo $(NAME_MSG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)


all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(CLEAN_MSG)
	@make clean -C $(LIBFT_DIR)

fclean:clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo $(FCLEAN_MSG)

re: fclean all

norm:
	norminette -v
	norminette $(SRC_DIR)
	norminette $(LIBFT_DIR)
	norminette $(includes)
