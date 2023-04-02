# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2023/04/02 10:28:36 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
OBJDIR		:=	./obj
SRC_DIR		:=	./srcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
CFLAGS  	+=  -fsanitize=address -g

HEADERS			:=  ./includes
LIBFT_DIR		:=	./lib/libft
LIBFT			:=	$(LIBFT_DIR)/libft.a
HEADERS			+=	$(LIBFT_DIR)/includes

INCLUDES		:=	$(addprefix -I , $(HEADERS))

SRC_FILE :=	main.c
SOURCES :=  $(addprefix $(SRC_DIR)/, $(SRC_FILE))
SRC_FILE :=  create_map.c set_ambient.c set_camera.c set_color.c set_light.c set_vec.c create_object.c check_color.c check_vec.c
SRC_FILE +=  util.c
SOURCES += $(addprefix ./srcs/create_map/, $(SRC_FILE))
OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
RM := rm -f

#Message
RED		:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
DEFAULT	:= \033[0m
NAME_MSG	:=	"$(GREEN) Compile $(NAME)$(DEFAULT)"
CLEAN_MSG	:=	"$(YELLOW) Delete $(OBJDIR)$(DEFAULT)"
FCLEAN_MSG	:=	"$(RED) Delete $(NAME)$(DEFAULT)"

.PHONY: all fclean clean re libft

$(NAME):  $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJECTS)
	echo $(NAME_MSG)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	-mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

all: $(NAME)

libft:
	make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR)
	@echo $(CLEAN_MSG)

fclean:clean
	@make fclean -C $(LIBFT_DIR)
	@echo $(FCLEAN_MSG)

re: fclean all

norm:
	norminette -v
	norminette $(SRC_DIR)
	norminette $(LIBFT_DIR)
	norminette $(includes)
