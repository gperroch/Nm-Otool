/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_applicatifs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:52:12 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/02 18:37:42 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_find_symtab(t_mach_header_64 *header,
	char to_display)
{
	t_symtab_command	*symtab_command;
	void					*symtab;
	void					*strtab;
	t_symbol_display		*list;

	//ft_display_load_command((struct load_command *)((char*)header + sizeof(t_mach_header_64)), header->ncmds);
	dump_mem(header, 16*10, 16, "");
	ft_locate_symbol_table(header, &symtab, &strtab, &symtab_command);
	list = ft_create_symbol_list(symtab, strtab, symtab_command, header);
	ft_sort_list_symbols(&list);
	if (to_display)
		ft_display_symbols(list);
	return (list);
}

void					ft_locate_symbol_table(t_mach_header_64 *header,
	void **symtab, void **strtab, t_symtab_command **symtab_command)
{
	t_load_command	*load_command;
	uint32_t			lc_counter;

	lc_counter = 0;
	load_command = (t_load_command*)((char*)header
		+ sizeof(t_mach_header_64));
	while (lc_counter < header->ncmds)
	{
		load_command = (t_load_command*)((char*)load_command
			+ load_command->cmdsize);
		lc_counter++;
		if (load_command->cmd == LC_SYMTAB)
			lc_counter = header->ncmds;
	}
	*symtab_command = (t_symtab_command*)load_command;
	*symtab = (char*)header + (*symtab_command)->symoff;
	*strtab = (char*)header + (*symtab_command)->stroff;
}

char						ft_find_section(void *header, int section_number)
{
	t_load_command			*load_cmd;
	t_segment_command_64	*segment_command;
	void						*section;
	int							section_counter;

	section_counter = 0;
	load_cmd = (t_load_command*)((char*)header + sizeof(t_mach_header_64));
	while (section_counter < section_number)
	{
		if (load_cmd->cmd == LC_SEGMENT || load_cmd->cmd == LC_SEGMENT_64)
			section_counter += ((t_segment_command_64*)load_cmd)->nsects;
		if (section_counter < section_number)
			load_cmd = (t_load_command*)((char*)load_cmd + load_cmd->cmdsize);
	}
	section_counter -= (((t_segment_command_64*)load_cmd)->nsects - 1);
	segment_command = (t_segment_command_64*)load_cmd;
	section = (char*)segment_command + sizeof(t_segment_command_64);
	while (section_counter < section_number)
	{
		section = (char*)section + sizeof(t_section_64);
		section_counter++;
	}
	return (ft_section_type(section));
}

char					ft_section_type(t_section_64 *section)
{
	char				res;

	res = 'S';
	res = !ft_strcmp(section->sectname, "__text") ? 'T' : res;
	res = !ft_strcmp(section->sectname, "__data") ? 'D' : res;
	res = !ft_strcmp(section->sectname, "__bss") ? 'B' : res;
	res = !ft_strcmp(section->sectname, "__common") ? 'C' : res;
	return (res);
}








/////////////////// OTOOL FUNCTIONS ////////////////////////

void					find_texttext_section(t_mach_header_64 *header) // Dans les .o le segment n'a pas de nom
{
	t_load_command	*load_command;
	t_section_64	*section;
	void				*content;
	uint32_t			ncmds;
	uint32_t			nsects;

	ncmds = 0;
	load_command = (t_load_command*)((char*)header + sizeof(t_mach_header_64));
	while (ncmds < header->ncmds)
	{
		nsects = 0;
		section = (t_section_64*)((char*)load_command + sizeof(t_segment_command_64));
		while (nsects < ((struct segment_command*)load_command)->nsects && ft_strcmp(section->sectname, "__text") && ft_strcmp(section->segname, "__TEXT"))
		{
			section = (t_section_64*)((char*)section + sizeof(t_section_64));
			nsects++;
		}
		if (!ft_strcmp(section->sectname, "__text") && !ft_strcmp(section->segname, "__TEXT"))
		{
			content = (char*)header + section->offset;
			ft_dump_mem(content, section->size, 16, header);
			ncmds = header->ncmds;
		}
		load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
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
		if ((i == 0 || i % col == 0) && ((t_mach_header_64*)header)->filetype == MH_OBJECT)
			printf("%016lx\t", (long)ptr - (long)init);
		else if ((i == 0 || i % col == 0) && ((t_mach_header_64*)header)->filetype == MH_EXECUTE)
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

int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats)
{
	int			fd;

	fd = open(file_name, O_RDONLY);
    if (fstat(fd, stats))
		return (-1);
	if ((*file_content = mmap(0, stats->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	close(fd);
	return (0);
}
