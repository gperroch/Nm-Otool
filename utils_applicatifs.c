/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_applicatifs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:52:12 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/01 14:39:02 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include "libft.h"
#include "nm.h"

t_symbol_display			*find_symtab(struct mach_header_64 *header, char to_display)
{
	struct load_command		*load_command;
	struct load_command		*tmp_load_command;
	struct symtab_command	*symtab_command;
	void					*symtab;
	void					*strtab;
	struct nlist_64			*nlist;
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	int						i;
	struct segment_command	*segment_command;
	void					*section;

	load_command = (struct load_command*)((char*)header + sizeof(struct mach_header_64));
	i = 0;
	tmp_load_command = load_command;
	while (i < header->ncmds)
	{
		tmp_load_command = (struct load_command*)((char*)tmp_load_command + tmp_load_command->cmdsize);
		i++;
		if (tmp_load_command->cmd == LC_SYMTAB)
			i = header->ncmds;
	}
	symtab_command = (struct symtab_command*)tmp_load_command;
	symtab = (char*)header + symtab_command->symoff;
	strtab = (char*)header + symtab_command->stroff;

	// Display des nlists
	i = 0;
	nlist = symtab;
	list = NULL;
	while (i < symtab_command->nsyms)
	{
		init_element(&list, &ptr);
		set_element(&ptr, nlist, header, strtab);
		nlist = (struct nlist_64*)((char*)nlist + sizeof(struct nlist_64));
		i++;
	}
	sort_list_symbols(&list);
	if (to_display)
		display_symbols(list);
	return (list);
}

void						set_element(t_symbol_display **ptr, struct nlist_64 *nlist, struct mach_header_64 *header, void *strtab)
{
	(*ptr)->value = nlist->n_value;
	(*ptr)->name = &((char*)strtab)[(nlist->n_un).n_strx];
	(*ptr)->type = 'U';
	(*ptr)->type = nlist->n_type & N_STAB ? '-' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_UNDF ? 'U' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_ABS ? 'A' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_INDR ? 'I' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_PBUD ? 'U' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_SECT ? find_section(header, nlist->n_sect) : (*ptr)->type;
	if (!(nlist->n_type & N_EXT))
		(*ptr)->type = ft_tolower((*ptr)->type);
}

void						init_element(t_symbol_display **list, t_symbol_display **ptr)
{
	if (!*list)
	{
		*list = (t_symbol_display*)malloc(sizeof(t_symbol_display));
		*ptr = *list;
		(*ptr)->next = NULL;
		(*ptr)->previous = NULL;
	}
	else
	{
		(*ptr)->next = (t_symbol_display*)malloc(sizeof(t_symbol_display));
		(*ptr)->next->previous = *ptr;
		(*ptr) = (*ptr)->next;
		(*ptr)->next = NULL;
	}
}

char						find_section(void *header, int section_number)
{
	struct load_command		*load_command;
	struct load_command 	*tmp_load_command;
	struct segment_command_64	*segment_command;
	void					*section;
	int						i;
	char					res;

	i = 0;
	load_command = (struct load_command*)((char*)header + sizeof(struct mach_header_64));
	tmp_load_command = load_command;
	while (i < section_number)
	{
		if (tmp_load_command->cmd == LC_SEGMENT || tmp_load_command->cmd == LC_SEGMENT_64)
			i += ((struct segment_command_64*)tmp_load_command)->nsects;
		if (i < section_number)
			tmp_load_command = (struct load_command*)((char*)tmp_load_command + tmp_load_command->cmdsize);
	}
	i -= ((struct segment_command_64*)tmp_load_command)->nsects;
	i++;
	segment_command = (struct segment_command_64*)tmp_load_command;
	section = (char*)segment_command + sizeof(struct segment_command_64);
	while (i < section_number)
	{
		section = (char*)section + sizeof(struct section_64);
		i++;
	}
	res = 'S';
	res = !ft_strcmp(((struct section_64*)section)->sectname, "__text") ? 'T' : res;
	res = !ft_strcmp(((struct section_64*)section)->sectname, "__data") ? 'D' : res;
	res = !ft_strcmp(((struct section_64*)section)->sectname, "__bss") ? 'B' : res;
	res = !ft_strcmp(((struct section_64*)section)->sectname, "__common") ? 'C' : res;
	return (res);
}

void					sort_list_symbols(t_symbol_display **list)
{
	t_symbol_display	*ptr;
	t_symbol_display	*ptr2;
	char				modified;

	modified = 1;
	while (modified)
	{
		modified = 0;
		ptr = *list;
		while (ptr && ptr->next)
		{
			ptr2 = ptr->next;
			if (ft_strcmp(ptr->name, ptr2->name) > 0)
			{
				if (ptr->previous)
					(ptr->previous)->next = ptr2;
				else
					*list = ptr2;
				if (ptr2->next)
					(ptr2->next)->previous = ptr;
				ptr->next = ptr2->next;
				ptr2->previous = ptr->previous;
				ptr->previous = ptr2;
				ptr2->next = ptr;
				modified = 1;
			}
			ptr = ptr2;
		}
	}
}

void				display_symbols(t_symbol_display *list)
{
	while (list)
	{
		if (list->type != 'U')
			printf("%016lx %c %s\n", list->value, list->type, list->name);
		else
			printf("%16c %c %s\n", ' ', list->type, list->name);
		list = list->next;
	}
}

void				is_static_library(void *file_content, char *file_name)
{
	char			arch[8];
	t_static_lib	*lib;
	t_static_lib	*file_object_header_line;
	struct ranlib	*ranlib;
	long int		ranlibs_size;
	char			*symbol_name;
	char			*file_object_name;
	void			*file_object;
	int diff;
	int	distance;
	t_lib_symbol	*list;
	t_lib_symbol	*ptr;

//	if (!ft_strcmp(file_content, "!<arch>"))
//		printf("StATIC LIB OK [%s]\n", arch);
	lib = file_content;
	ranlibs_size = lib->ranlibs_size;
	ranlib = (struct ranlib*)((char*)file_content + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		symbol_name = (char*)file_content + sizeof(t_static_lib) + lib->ranlibs_size + ranlib->ran_off;
		file_object_header_line = (t_static_lib*)((char*)file_content + (ranlib->ran_un).ran_strx);
		diff = (char*)file_object_header_line->end_identifier + ft_strlen(file_object_header_line->end_identifier) - (char*)file_object_header_line;
		distance = ((diff / 8) + 1) * 8;
		distance = diff % 8 > 4 ? distance + 8 : distance;
		file_object_name = (char*)file_content + sizeof(lib->file_identifier) + (ranlib->ran_un).ran_strx;
		file_object = (char*)file_object_header_line + distance;
		ft_list_lib_symbols(&list, symbol_name, file_object_name, file_object);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib)); // VERIFIER LA PRESENCE DE ran_name AVEC UN IFDEF __LP64__
		ranlibs_size -= sizeof(struct ranlib);
	}
	ptr = list;
	while (ptr)
	{
		printf("\n%s(%s):\n", file_name, ptr->file_object_name);
		find_symtab(ptr->file_object, 1);
		ptr = ptr->next;
	}
}

void				ft_list_lib_symbols(t_lib_symbol **list, char *symbol_name, char *file_object_name, void *file_object)
{
	t_lib_symbol	*new_symbol;
	t_lib_symbol	*ptr;
	// Parsing pour les NULL a faire ici
	ptr = *list;
	new_symbol = (t_lib_symbol*)malloc(sizeof(t_lib_symbol));
	ft_bzero(new_symbol, sizeof(t_lib_symbol));
	if (ft_check_symbol_in_file_object(symbol_name, file_object))
		new_symbol->symbol_in_file_object = 1;
	if (!*list)
		*list = new_symbol;
	else
	{
		if (!ft_strcmp(ptr->file_object_name, file_object_name) && ptr->symbol_in_file_object)
		{
			free(new_symbol);
			return ;
		}
		while (ptr->next)
		{
			ptr = ptr->next;
			if (!ft_strcmp(ptr->file_object_name, file_object_name) && ptr->symbol_in_file_object)
			{
				free(new_symbol);
				return ;
			}
		}
		ptr->next = new_symbol;
		new_symbol->previous = ptr;
		ptr = ptr->next;
	}
	new_symbol->symbol_name = symbol_name;
	new_symbol->file_object_name = file_object_name;
	new_symbol->file_object = file_object;
}

int				ft_check_symbol_in_file_object(char *symbol_name, void *file_object)
{
	t_symbol_display	*list;

	list = find_symtab(file_object, 0);
	while (list)
	{
		if (!ft_strcmp(list->name, symbol_name) && list->type >= 65 && list->type <= 90 && list->type != 'U')
			return (1);
		list = list->next;
	}
	return (0);
}

/////////////////// OTOOL FUNCTIONS ////////////////////////

void					find_texttext_section(struct mach_header_64 *header) // Dans les .o le segment n'a pas de nom
{
	struct load_command	*load_command;
	struct section_64	*section;
	void				*content;
	int					ncmds;
	int					nsects;

	ncmds = 0;
	load_command = (struct load_command*)((char*)header + sizeof(struct mach_header_64));
	while (ncmds < header->ncmds)
	{
		nsects = 0;
		section = (struct section_64*)((char*)load_command + sizeof(struct segment_command_64));
		while (nsects < ((struct segment_command*)load_command)->nsects && ft_strcmp(section->sectname, "__text") && ft_strcmp(section->segname, "__TEXT"))
		{
			section = (struct section_64*)((char*)section + sizeof(struct section_64));
			nsects++;
		}
		if (!ft_strcmp(section->sectname, "__text") && !ft_strcmp(section->segname, "__TEXT"))
		{
			content = (char*)header + section->offset;
			ft_dump_mem(content, section->size, 16, header);
			ncmds = header->ncmds;
		}
		load_command = (struct load_command*)((char*)load_command + load_command->cmdsize);
		ncmds++;
	}
}

void		ft_dump_mem(void *ptr, int len, int col, void *header)
{
	int		i;
	char	*mem;
	char	*init;

	mem = ptr;
	init = ptr;
	i = 0;
	while (i < len)
	{
		if ((i == 0 || i % col == 0) && ((struct mach_header_64*)header)->filetype == MH_OBJECT)
			printf("%016lx\t", (long)ptr - (long)init);
		else if ((i == 0 || i % col == 0) && ((struct mach_header_64*)header)->filetype == MH_EXECUTE)
			printf("%016lx\t", (long)ptr - (int)header);
		else if (i == 0 || i % col == 0)
			printf("%016lx\t", (long)ptr);
		printf("%02hhx ", mem[i]);
		ptr++;
		i++;
		if (i == len || i % col == 0)
			printf("\n");
	}
}

void			find_texttext_static_library(void *file_content, char *argv)
{
	char			arch[8];
	t_static_lib	*lib;
	t_static_lib	*file_object_header_line;
	struct ranlib	*ranlib;
	long int		ranlibs_size;
	char			*symbol_name;
	char			*file_object_name;
	void			*file_object;
	int diff;
	int	distance;
	t_lib_symbol	*list;
	t_lib_symbol	*ptr;

/*	dump_mem(file_content, 64, 16, "init");
	dump_mem((char*)file_content + 60, 64, 16, "+60");
	dump_mem((char*)file_content + 88, 64, 16, "+88"); // Le +88 doit dependre du nom du fichier. Comme pour atteindre les headers mach des objets avec la variable 'distance'.
*/
	lib = file_content;
	ranlibs_size = lib->ranlibs_size;
	ranlib = (struct ranlib*)((char*)file_content + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		symbol_name = (char*)file_content + sizeof(t_static_lib) + lib->ranlibs_size + ranlib->ran_off;
		file_object_header_line = (t_static_lib*)((char*)file_content + (ranlib->ran_un).ran_strx);
		diff = (char*)file_object_header_line->end_identifier + ft_strlen(file_object_header_line->end_identifier) - (char*)file_object_header_line;
		distance = ((diff / 8) + 1) * 8;
		distance = diff % 8 > 4 ? distance + 8 : distance;
		file_object_name = (char*)file_content + sizeof(lib->file_identifier) + (ranlib->ran_un).ran_strx;
		file_object = (char*)file_object_header_line + distance;
		ft_list_lib_symbols(&list, symbol_name, file_object_name, file_object);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib)); // VERIFIER LA PRESENCE DE ran_name AVEC UN IFDEF __LP64__
		ranlibs_size -= sizeof(struct ranlib);
	}
	ptr = list;
	while (ptr)
	{
		printf("%s(%s):\nContents of (__TEXT,__text) section\n", argv, ptr->file_object_name);
		find_texttext_section(ptr->file_object);
		ptr = ptr->next;
	}
}
