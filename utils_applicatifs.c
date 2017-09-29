/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_applicatifs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:52:12 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/29 15:53:08 by gperroch         ###   ########.fr       */
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
		if (!list)
		{
			list = (t_symbol_display*)malloc(sizeof(t_symbol_display));
			ptr = list;
			ptr->next = NULL;
			ptr->previous = NULL;
		}
		else
		{
			ptr->next = (t_symbol_display*)malloc(sizeof(t_symbol_display));
			ptr->next->previous = ptr;
			ptr = ptr->next;
			ptr->next = NULL;
		}
		ptr->value = nlist->n_value;
		ptr->name = &((char*)strtab)[(nlist->n_un).n_strx];

		ptr->type = 'U';
		ptr->type = nlist->n_type & N_STAB ? '-' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_UNDF ? 'U' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_ABS ? 'A' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_INDR ? 'I' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_PBUD ? 'U' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_SECT ? find_section(header, nlist->n_sect) : ptr->type;

		//Passage en minuscule pour les symboles locaux
		printf("nlist->n_desc:%hd value:%ld [%s]\n", nlist->n_desc, nlist->n_value, ptr->name);
		if ((nlist->n_desc & REFERENCE_TYPE) & REFERENCE_FLAG_DEFINED || (nlist->n_desc & REFERENCE_TYPE) & REFERENCE_FLAG_PRIVATE_DEFINED)
			printf("==> %s is LOCAL SYMBOL\n", ptr->name);
		///////////////////////////////////////////////

		nlist = (struct nlist_64*)((char*)nlist + sizeof(struct nlist_64));
		i++;
	}
	sort_list_symbols(&list);
	ptr = list;
	while (ptr)
	{
		if (ptr->value)
			printf("%016lx %c %s\n", ptr->value, ptr->type, ptr->name);
		else
			printf("%16c %c %s\n", ' ', ptr->type, ptr->name);
		ptr = ptr->next;
	}
	//////////////////////////////
	nlist = symtab;
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
	segment_command = tmp_load_command;
	section = (char*)segment_command + sizeof(struct segment_command_64);
	while (i < section_number)
	{
		section = (char*)section + ((struct section_64*)section)->size;
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
