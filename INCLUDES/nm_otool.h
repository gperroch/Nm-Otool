/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:04:15 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/18 12:56:06 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "libft.h"

typedef struct load_command			t_load_command;
typedef struct symtab_command		t_symtab_command;
typedef struct mach_header_64		t_mach_header_64;
typedef struct segment_command_64	t_segment_command_64;
typedef struct section_64			t_section_64;
typedef struct				s_symbol_display
{
	long int				value;
	char					type;
	char					*name;
	struct s_symbol_display	*next;
	struct s_symbol_display	*previous;
}							t_symbol_display;
typedef struct				s_static_lib
{
	char					file_identifier[60];
	char					end_identifier[8];
	char					sort_order[20];
	long int				ranlibs_size;
}							t_static_lib;
typedef struct				s_lib_symbol
{
	char					*symbol_name;
	char					*file_object_name;
	void					*file_object;
	char					symbol_in_file_object;
	struct s_lib_symbol		*next;
	struct s_lib_symbol		*previous;
}							t_lib_symbol;

t_symbol_display			*ft_find_symtab(struct mach_header_64 *header,
	char to_display);
void						ft_locate_symbol_table(
	struct mach_header_64 *header, void **symtab,
	void **strtab, struct symtab_command **symtab_command);
t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab,
	struct symtab_command *symtab_command, struct mach_header_64 *header);
void						ft_set_element(t_symbol_display **ptr,
	struct nlist_64 *nlist, struct mach_header_64 *header, void *strtab);
void						ft_init_element(t_symbol_display **list,
	t_symbol_display **ptr);
void						ft_display_symbols(t_symbol_display *list);
char						ft_find_section(void *header, int section_number);
char						ft_section_type(struct section_64 *section);
void						ft_sort_list_symbols(t_symbol_display **list);
void						ft_set_previous_and_next(t_symbol_display *ptr,
	t_symbol_display *ptr2, t_symbol_display **list);
void						ft_static_library(void *file_content,
	char *file_name);
void						ft_display_static_library_symbols(
	t_lib_symbol *list, char *file_name);
void						ft_find_ranlib_symtab(void *file_content,
	t_static_lib *lib, struct ranlib *ranlib, t_lib_symbol **list);
int							ft_add_symbol_to_list(t_lib_symbol *ptr,
	t_lib_symbol *new_symbol, char *file_object_name);
int							ft_mapping_file(char *file_name,
	void **file_content, struct stat *stats);
void						ft_iter_texttext_sections(
	t_load_command *load_command, t_mach_header_64 *header, uint32_t *ncmds);
void						*ft_find_ranlib_symbols(void *file_content,
	struct ranlib *ranlib, t_static_lib *lib, t_lib_symbol **list);
void						ft_find_texttext_section(
	struct mach_header_64 *header);
int							ft_calculate_distance_file_object(
	t_static_lib *file_object_header_line);
void						ft_list_lib_symbols(t_lib_symbol **list,
	char *symbol_name, char *file_object_name, void *file_object);
int							ft_check_symbol_in_file_object(char *symbol_name,
	void *file_object);
void						ft_find_texttext_static_library(void *file_content,
	char *argv);
void						ft_dump_mem(void *ptr, int len, int col,
	void *header);

#endif
