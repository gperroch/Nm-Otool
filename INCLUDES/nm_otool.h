/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:04:15 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/01 15:00:09 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
#define NM_OTOOL_H

# include <mach-o/ranlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include "libft.h"

typedef struct				s_symbol_display
{
	long int				value;
	char					type;
	char					*name;
	struct s_symbol_display	*next;
	struct s_symbol_display	*previous;
}							t_symbol_display;
typedef struct				s_static_lib // ATTENTION A LA TAILLE DU NOM DU FICHIER. HEADER A MODIFIER. AJOUTER LES 5 VARIABLES DU FILE_IDENTIFIER
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

void					sort_list_symbols(t_symbol_display **list);
int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats);
void			ft_display_header(struct mach_header_64 *header);
void			ft_display_load_command(struct load_command *load_command, int ncmds);
void			dump_mem(void *ptr, int len, int col, char *name);
char			*load_command_type(uint32_t cmd);
void			display_load_symtab(struct load_command *load_command);
void			display_load_dysymtab(struct load_command *load_command);
void			test_strtab(char *ptr, int size);
char			find_section(void *header, int section_number);
void				display_symbols(t_symbol_display *list);
void						init_element(t_symbol_display **list, t_symbol_display **ptr);
void						set_element(t_symbol_display **ptr, struct nlist_64 *nlist, struct mach_header_64 *header, void *strtab);

void					listing_symbols(struct load_command *tmp_load_command, t_symbol_display **list, struct mach_header_64 *header, int i);
int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats);
void			ft_display_header(struct mach_header_64 *header);
void			ft_display_load_command(struct load_command *load_command, int ncmds);
void			dump_mem(void *ptr, int len, int col, char *name);
char			*load_command_type(uint32_t cmd);
t_symbol_display			*find_symtab(struct mach_header_64 *header, char to_display);
//////////////////////////////////
void				is_static_library(void *file_content, char *file_name);
void					sort_list_lib_symbols(t_lib_symbol **list);
void				ft_list_lib_symbols(t_lib_symbol **list, char *symbol_name, char *file_object_name, void *file_object);
int				ft_check_symbol_in_file_object(char *symbol_name, void *file_object);
void					find_texttext_section(struct mach_header_64 *header);
void		ft_dump_mem(void *ptr, int len, int col, void *header);
void			find_texttext_static_library(void *file_content, char *argv);

#endif
