# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/01 14:54:19 by gperroch          #+#    #+#              #
#    Updated: 2018/03/14 14:32:27 by gperroch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = ft_nm
NAME_OTOOL = ft_otool

SRC_NM_PATH = ./SOURCES/
SRC_NM_NAME =	main.c \
				ft_errors_nm.c \
				ft_mapping_file.c \
				ft_analyse_file.c \
				ft_find_symtab.c \
				ft_create_symbol_list.c \
				ft_locate_symbol_table.c \
				ft_find_section.c \
				ft_fat_arch.c \
				ft_proceed_macho_nm.c \
				ft_proceed_fat_nm.c \
				ft_proceed_lib_nm.c \
				ft_free_static_library_symbols.c \
				ft_list_lib_symbols.c \
				ft_add_symbol_to_list.c \
				ft_check_symbol_in_file_object.c \
				ft_free_list_symbols.c \
				ft_init_gen.c \
				ft_set_element.c \
				ft_init_element.c \
				ft_section_type.c \
				ft_has_print.c \
				ft_display_symbols.c \
				ft_sort_list_symbols.c \
				ft_set_previous_and_next.c \
				ft_iterate_fat_arch.c \
				ft_arch_gateway.c \
				ft_get_arch_type.c \
				ft_bounds_security.c \
				ft_swap_endian_32bit.c \
				ft_static_library.c \
				ft_find_ranlib_symtab.c \
				ft_display_static_library_symbols.c \
				ft_find_arch64.c \
				dump_mem.c \
				ft_dump_mem.c

SRC_OTOOL_PATH = ./SOURCES/
SRC_OTOOL_NAME =	main.c \
					ft_errors_otool.c \
					ft_mapping_file.c \
					ft_analyse_file.c \
					ft_find_symtab.c \
					ft_create_symbol_list.c \
					ft_locate_symbol_table.c \
					ft_find_section.c \
					ft_fat_arch.c \
					ft_proceed_macho_otool.c \
					ft_proceed_fat_otool.c \
					ft_proceed_lib_otool.c \
					ft_free_static_library_symbols.c \
					ft_list_lib_symbols.c \
					ft_add_symbol_to_list.c \
					ft_free_list_symbols.c \
					ft_check_symbol_in_file_object.c \
					ft_init_gen.c \
					ft_set_element.c \
					ft_init_element.c \
					ft_section_type.c \
					ft_has_print.c \
					ft_display_symbols.c \
					ft_sort_list_symbols.c \
					ft_set_previous_and_next.c \
					ft_iterate_fat_arch.c \
					ft_arch_gateway.c \
					ft_get_arch_type.c \
					ft_bounds_security.c \
					ft_swap_endian_32bit.c \
					ft_find_texttext_section.c \
					ft_iter_texttext_sections.c \
					ft_find_texttext_static_library.c \
					ft_find_ranlib_symbols.c \
					ft_calculate_distance_file_object.c \
					ft_find_arch64.c \
					dump_mem.c \
					ft_dump_mem.c

OBJ_NM_PATH = ./OBJECTS/
OBJ_OTOOL_PATH = ./OBJECTS/
INC_PATH = ./INCLUDES/
LIBFT = libft/libft.a
LIB_PATH = ./libft/
CC = gcc
CFLAGS = -Wall -Wextra -Werror

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
	@echo "$(NAME_NM) complete !"

$(NAME_OTOOL): $(LIBFT) $(OBJ_OTOOL)
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "$(NAME_OTOOL) complete !"

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

re: fclean all

$(LIBFT):
	make -C $(LIB_PATH)
