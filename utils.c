/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 09:35:47 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/29 13:26:09 by gperroch         ###   ########.fr       */
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

int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats);
void			ft_display_header(struct mach_header_64 *header);
void			ft_display_load_command(struct load_command *load_command, int ncmds);
void			dump_mem(void *ptr, int len, int col, char *name);
char			*load_command_type(uint32_t cmd);
void			display_load_symtab(struct load_command *load_command);
void			display_load_dysymtab(struct load_command *load_command);
void			test_strtab(char *ptr, int size);

void			ft_display_header(struct mach_header_64 *header)
{
	printf("Magic number: %x\n", header->magic);
	printf("cputype: %d\n", header->cputype);
	printf("cpusubtype: %d\n", header->cpusubtype);
	printf("filetype: %d\n", header->filetype);
	printf("ncmds: %u\n", header->ncmds);
	printf("sizeofcmds: %d\n", header->sizeofcmds);
	printf("flags: %x\n", header->flags);
	printf("reserved: %x\n", header->reserved);
}

void					ft_display_load_command(struct load_command *load_command, int ncmds)
{
	int					i;
	struct load_command *ptr;

	i = 0;
	ptr = load_command;
	printf("LOAD_COMMAND\n");

	while (i < ncmds)
	{
		printf("\ncommand type: %s [%u][n%d | %p]\n", load_command_type(ptr->cmd), ptr->cmd, i, ptr);
		printf("cmdsize: %u\n", ptr->cmdsize);
		if (ptr->cmd == LC_SYMTAB)
		{
			display_load_symtab(ptr);
			dump_mem(ptr, ptr->cmdsize + sizeof(struct load_command), 16, ft_itoa(i));
		}
		if (ptr->cmd == LC_DYSYMTAB)
		{
			display_load_dysymtab(ptr);
			dump_mem(ptr, ptr->cmdsize + sizeof(struct load_command), 16, ft_itoa(i));
		}
		ptr = (struct load_command*)((char*)ptr + ptr->cmdsize);
		i++;
	}
}

char					*load_command_type(uint32_t cmd)
{
	char				*type;

	type = "NULL";
	type = cmd == LC_SEGMENT_64 ? ft_strdup("LC_SEGMENT_64") : type;
	type = cmd == LC_SEGMENT ? ft_strdup("LC_SEGMENT") : type;
	type = cmd == LC_SYMTAB ? ft_strdup("LC_SYMTAB") : type;
	type = cmd == LC_DYSYMTAB ? ft_strdup("LC_DYSYMTAB") : type;
	type = cmd == LC_THREAD ? ft_strdup("LC_THREAD") : type;
	type = cmd == LC_UNIXTHREAD ? ft_strdup("LC_UNIXTHREAD") : type;
	type = cmd == LC_LOAD_DYLIB ? ft_strdup("LC_LOAD_DYLIB") : type;
	type = cmd == LC_ID_DYLIB ? ft_strdup("LC_ID_DYLIB") : type;
	type = cmd == LC_PREBOUND_DYLIB ? ft_strdup("LC_PREBOUND_DYLIB") : type;
	type = cmd == LC_LOAD_DYLINKER ? ft_strdup("LC_LOAD_DYLINKER") : type;
	type = cmd == LC_ID_DYLINKER ? ft_strdup("LC_ID_DYLINKER") : type;
	type = cmd == LC_ROUTINES ? ft_strdup("LC_ROUTINES") : type;
	type = cmd == LC_TWOLEVEL_HINTS ? ft_strdup("LC_TWOLEVEL_HINTS ") : type;
	type = cmd == LC_SUB_FRAMEWORK ? ft_strdup("LC_SUB_FRAMEWORK") : type;
	type = cmd == LC_SUB_UMBRELLA ? ft_strdup("LC_SUB_UMBRELLA") : type;
	type = cmd == LC_SUB_LIBRARY ? ft_strdup("LC_SUB_LIBRARY") : type;
	type = cmd == LC_SUB_CLIENT ? ft_strdup("LC_SUB_CLIENT") : type;
	type = cmd == LC_DYLD_INFO_ONLY ? ft_strdup("LC_DYLD_INFO_ONLY") : type;
	type = cmd == LC_SOURCE_VERSION ? ft_strdup("LC_SOURCE_VERSION") : type;
	type = cmd == LC_DATA_IN_CODE ? ft_strdup("LC_DATA_IN_CODE") : type;
	type = cmd == LC_FUNCTION_STARTS ? ft_strdup("LC_FUNCTION_STARTS") : type;
	type = cmd == LC_UUID ? ft_strdup("LC_UUID") : type;
	type = cmd == LC_VERSION_MIN_MACOSX ? ft_strdup("LC_VERSION_MIN_MACOSX") : type;
	type = cmd == LC_MAIN ? ft_strdup("LC_MAIN") : type;
	return (type);
}

void						display_load_symtab(struct load_command *load_command)
{
	struct symtab_command	*ptr;

	ptr = (struct symtab_command*)load_command;
	printf("cmd:%u\n", ptr->cmd);
	printf("cmdsize:%u\n", ptr->cmdsize);
	printf("symoff:%u\n", ptr->symoff);
	printf("nsyms:%u\n", ptr->nsyms);
	printf("stroff:%u\n", ptr->stroff);
	printf("strsize:%u\n", ptr->strsize);
}

void						display_load_dysymtab(struct load_command *load_command)
{
	struct dysymtab_command	*ptr;

	ptr = (struct dysymtab_command*)load_command;
	printf("cmd:%u\n", ptr->cmd);
	printf("cmdsize:%u\n", ptr->cmdsize);
	printf("ilocalsym:%u\n", ptr->ilocalsym);
	printf("nlocalsym:%u\n", ptr->nlocalsym);
	printf("iextdefsym:%u\n", ptr->iextdefsym);
	printf("nextdefsym:%u\n", ptr->nextdefsym);
	printf("iundefsym:%u\n", ptr->iundefsym);
	printf("nundefsym:%u\n", ptr->nundefsym);
	printf("tocoff:%u\n", ptr->tocoff);
	printf("ntoc:%u\n", ptr->ntoc);
	printf("modtaboff:%u\n", ptr->modtaboff);
	printf("nmodtab:%u\n", ptr->nmodtab);
	printf("extrefsymoff:%u\n", ptr->extrefsymoff);
	printf("nextrefsyms:%u\n", ptr->nextrefsyms);
	printf("indirectsymoff:%u\n", ptr->indirectsymoff);
	printf("nindirectsyms:%u\n", ptr->nindirectsyms);
	printf("extreloff:%u\n", ptr->extreloff);
	printf("nextrel:%u\n", ptr->nextrel);
	printf("locreloff:%u\n", ptr->locreloff);
	printf("nlocrel:%u\n", ptr->nlocrel);
}

////////////////////APPLICATIF////////////////////////

void						find_symtab(struct mach_header_64 *header)
{
	struct load_command		*load_command;
	struct symtab_command	*symtab_command;
	void					*symtab;
	void					*strtab;
	struct nlist_64			*nlist;
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	int						i;

	load_command = (struct load_command*)((char*)header + sizeof(struct mach_header_64));
	i = 0;
	while (i < header->ncmds)
	{
		load_command = (struct load_command*)((char*)load_command + load_command->cmdsize);
		i++;
		if (load_command->cmd == LC_SYMTAB)
			i = header->ncmds;
	}
	symtab_command = (struct symtab_command*)load_command;
//	display_load_symtab(load_command);
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
		ptr->type = 'U';
		ptr->type = nlist->n_type & N_STAB ? '-' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_UNDF ? 'T' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_ABS ? 'A' : ptr->type;
		ptr->type = (nlist->n_type & N_TYPE) & N_SECT ? 'S' : ptr->type; // => T, D, B. Ou est C ?
		ptr->type = (nlist->n_type & N_TYPE) & N_PBUD ? 'T' : ptr->type;
//		ptr->type = nlist->n_type & N_EXT ? 'I' : ptr->type;
		ptr->name = &((char*)strtab)[(nlist->n_un).n_strx];

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
