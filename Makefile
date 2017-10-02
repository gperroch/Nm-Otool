# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/01 14:54:19 by gperroch          #+#    #+#              #
#    Updated: 2017/10/02 18:35:37 by gperroch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = ft_nm
NAME_OTOOL = ft_otool

SRC_NM_PATH = ./SOURCES/
SRC_NM_NAME =	nm.c \
				utils_applicatifs.c \
				symbol_list.c \
				sort_list_symbols.c \
				static_library.c \
				lib_list_symbol.c \
				utils.c \
				dump_mem.c

SRC_OTOOL_PATH = ./SOURCES/
SRC_OTOOL_NAME =	otool.c \
					utils_applicatifs.c \
					symbol_list.c \
					sort_list_symbols.c \
					static_library.c \
					lib_list_symbol.c \
					utils.c \
					dump_mem.c

OBJ_NM_PATH = ./OBJECTS/
OBJ_OTOOL_PATH = ./OBJECTS/
INC_PATH = ./INCLUDES/
LIBFT = libft/libft.a
LIB_PATH = ./libft/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -g

OBJ_NM_NAME = $(SRC_NM_NAME:.c=.o)
OBJ_NM = $(addprefix $(OBJ_NM_PATH),$(OBJ_NM_NAME))

OBJ_OTOOL_NAME = $(SRC_OTOOL_NAME:.c=.o)
OBJ_OTOOL = $(addprefix $(OBJ_OTOOL_PATH),$(OBJ_OTOOL_NAME))

LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))
LDFLAGS = $(LIB)

.PHONY: all clean fclean re libft

all: $(LIBFT) $(NAME_NM) $(NAME_OTOOL)

$(NAME_NM): $(LIBFT) $(OBJ_NM)
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "$(NAME_NM) complete ! 🍻 "

$(NAME_OTOOL): $(LIBFT) $(OBJ_OTOOL)
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "$(NAME_OTOOL) complete ! 🍻 "

$(OBJ_NM_PATH)%.o: $(SRC_NM_PATH)%.c
	@mkdir $(OBJ_NM_PATH) 2> /dev/null || echo  > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_OTOOL_PATH)%.o: $(SRC_OTOOL_PATH)%.c
	@mkdir $(OBJ_OTOOL_PATH) 2> /dev/null || echo  > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJ_NM)
	rm -rf $(OBJ_OTOOL)
	rmdir $(OBJ_NM_PATH) obj 2> /dev/null || echo  > /dev/null
	rmdir $(OBJ_OTOOL_PATH) obj 2> /dev/null || echo  > /dev/null
	make clean -C $(LIB_PATH)

fclean: clean
	rm -rf $(NAME_NM) $(NAME_OTOOL)
	make fclean -C $(LIB_PATH)
	@echo "Everything's clean, master !"

re: fclean all

$(LIBFT):
	make -C $(LIB_PATH)
