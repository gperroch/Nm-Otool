/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 09:35:47 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/01 13:51:44 by gperroch         ###   ########.fr       */
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
		if (ptr->cmd == LC_SEGMENT_64 || ptr->cmd == LC_SEGMENT)
		{
			printf("segname:%s\nnsects:%d\n", ((struct segment_command_64*)ptr)->segname, ((struct segment_command_64*)ptr)->nsects);
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
