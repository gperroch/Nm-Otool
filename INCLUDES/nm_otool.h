/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:04:15 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/25 16:48:58 by gperroch         ###   ########.fr       */
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
# include <mach-o/fat.h>
# include "libft.h"

#define MACH_HEADER 1
#define SEGMENT_COMMAND 2
#define SECTION 3
#define FAT_ARCH 4
#define SIZE_MACH_HEADER_32 sizeof(struct mach_header)
#define SIZE_MACH_HEADER_64 sizeof(struct mach_header_64)
#define SIZE_SEGMENT_COMMAND_32 sizeof(struct segment_command)
#define SIZE_SEGMENT_COMMAND_64 sizeof(struct segment_command_64)
#define SIZE_SECTION_32 sizeof(struct section)
#define SIZE_SECTION_64 sizeof(struct section_64)
#define SIZE_FAT_ARCH_32 sizeof(struct fat_arch)
#define SIZE_FAT_ARCH_64 sizeof(struct fat_arch_64)

typedef struct load_command			t_load_command;
typedef struct symtab_command		t_symtab_command;
typedef struct mach_header_64		t_mach_header_64;
typedef struct mach_header			t_mach_header;
typedef struct segment_command_64	t_segment_command_64;
typedef struct segment_command		t_segment_command;
typedef struct section_64			t_section_64;

typedef struct				s_generic_file
{
	t_mach_header_64		*header;
	struct nlist_64			*nlist_64; // 64bit
	struct nlist			*nlist; // 32bit
	/* Valeurs de nlist */
	uint8_t n_type;     /* type flag, see below */
	uint8_t n_sect;     /* section number or NO_SECT */
	int16_t n_desc;     /* see <mach-o/stab.h> */
	uint32_t n_value;
	uint32_t n_strx;
	/* Valeurs de segment_command */
	uint32_t    cmd;        /* LC_SEGMENT_64 */
 	uint32_t    cmdsize;    /* includes sizeof section_64 structs */
 	char        segname[16];    /* segment name */
 	uint64_t    vmaddr;     /* memory address of this segment */
 	uint64_t    vmsize;     /* memory size of this segment */
 	uint64_t    fileoff;    /* file offset of this segment */
 	uint64_t    filesize;   /* amount to map from the file */
 	vm_prot_t   maxprot;    /* maximum VM protection */
 	vm_prot_t   initprot;   /* initial VM protection */
 	uint32_t    nsects;     /* number of sections in segment */
 	uint32_t    flags;
	int						arch;
}							t_generic_file;

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

//t_symbol_display			*ft_find_symtab(struct mach_header_64 *header, char to_display); // 64bit
t_symbol_display			*ft_find_symtab(t_generic_file *gen, char to_display); // GATEWAY
//void						ft_locate_symbol_table(struct mach_header_64 *header, void **symtab, void **strtab, struct symtab_command **symtab_command); // 64bit
void						ft_locate_symbol_table(t_generic_file *gen, void **symtab, void **strtab, t_symtab_command **symtab_command); // GATEWAY
//t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab, struct symtab_command *symtab_command, struct mach_header_64 *header); // 64bit
t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab, t_symtab_command *symtab_command, t_generic_file *gen); // GATEWAY
//void						ft_set_element(t_symbol_display **ptr, struct nlist_64 *nlist, struct mach_header_64 *header, void *strtab); // 64bit
void						ft_set_element(t_symbol_display **ptr, t_generic_file *gen, void *strtab); // GATEWAY
void						ft_init_element(t_symbol_display **list, t_symbol_display **ptr);
//void						ft_display_symbols(t_symbol_display *list); // 64bit
void						ft_display_symbols(t_symbol_display *list, t_generic_file *gen); // GATEWAY
//char						ft_find_section(void *header, int section_number); // 64bit
char						ft_find_section(t_generic_file *gen); // GATEWAY
char						ft_section_type(struct section_64 *section);
void						ft_sort_list_symbols(t_symbol_display **list);
void						ft_set_previous_and_next(t_symbol_display *ptr, t_symbol_display *ptr2, t_symbol_display **list);
void						ft_static_library(void *file_content, char *file_name);
void						ft_display_static_library_symbols(t_lib_symbol *list, char *file_name);
void						ft_find_ranlib_symtab(void *file_content, t_static_lib *lib, struct ranlib *ranlib, t_lib_symbol **list);
int							ft_add_symbol_to_list(t_lib_symbol *ptr, t_lib_symbol *new_symbol, char *file_object_name);
int							ft_mapping_file(char *file_name, void **file_content, struct stat *stats);
void						ft_iter_texttext_sections(t_load_command *load_command, t_mach_header_64 *header, uint32_t *ncmds);
void						*ft_find_ranlib_symbols(void *file_content, struct ranlib *ranlib, t_lib_symbol **list);
void						ft_find_texttext_section(struct mach_header_64 *header);
int							ft_calculate_distance_file_object(t_static_lib *file_object_header_line);
void						ft_list_lib_symbols(t_lib_symbol **list, char *symbol_name, char *file_object_name, void *file_object);
int							ft_check_symbol_in_file_object(char *symbol_name, void *file_object);
void						ft_find_texttext_static_library(void *file_content, char *argv);
void						ft_dump_mem(void *ptr, int len, int col, void *header);
void						ft_free_list_symbols(t_symbol_display *list);
void						ft_free_static_library_symbols(t_lib_symbol *list);

int			ft_arch_gateway(int arch, int element);
void					ft_fat_arch(void *file_content, char *file_name, unsigned int magic, off_t file_size);
void					ft_iterate_fat_arch(void *file_content, uint64_t offset, int arch, off_t file_size);
int						ft_swap_endian_32bit(int nbr);

void		dump_mem(void *ptr, int len, int col, char *name);
#endif
