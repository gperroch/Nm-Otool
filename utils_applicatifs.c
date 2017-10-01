/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_applicatifs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:52:12 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/01 10:16:37 by gperroch         ###   ########.fr       */
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

void						find_symtab(struct mach_header_64 *header)
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
	display_symbols(list);
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

void				is_static_library(void *file_content)
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

	ft_strncpy(arch, file_content, 7);
	if (!ft_strcmp(arch, "!<arch>"))
		printf("StATIC LIB OK [%s]\n", arch);
	lib = file_content;
	printf("file_identifier:[%s]\n", lib->file_identifier);
	printf("end_identifier:[%s]\n", lib->end_identifier);
	printf("sort_order:[%s]\n", lib->sort_order);
	printf("ranlibs_size:[%ld]\n", lib->ranlibs_size);
	ranlibs_size = lib->ranlibs_size;
	ranlib = (char*)file_content + sizeof(t_static_lib);
	//ranlibs_size -= sizeof(struct ranlib);
	while (ranlibs_size)
	{
		symbol_name = (char*)file_content + sizeof(t_static_lib) + lib->ranlibs_size + ranlib->ran_off;

		file_object_header_line = (char*)file_content + (ranlib->ran_un).ran_strx; // Rename tmp en file_object_header_line
		diff = (char*)file_object_header_line->end_identifier + ft_strlen(file_object_header_line->end_identifier) - (char*)file_object_header_line;
		distance = ((diff / 8) + 1) * 8;
		distance = diff % 8 > 4 ? distance + 8 : distance;

		file_object_name = (char*)file_content + sizeof(lib->file_identifier) + (ranlib->ran_un).ran_strx;
		printf("symbol_name:%s file_object_name:%s\n", symbol_name, file_object_name);
		file_object = (char*)file_object_header_line + distance;
//		printf("\n%s:\n", file_object_name);
//		find_symtab(file_object);
		dump_mem(file_object, 32, 16, "object");
		ranlib = (char*)ranlib + sizeof(ranlib); // VERIFIER LA PRESENCE DE ran_name AVEC UN IFDEF __LP64__
		ranlibs_size -= sizeof(struct ranlib);
	}
}
