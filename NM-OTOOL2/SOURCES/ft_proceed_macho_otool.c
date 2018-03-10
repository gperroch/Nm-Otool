/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_macho_otool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:16:02 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/10 15:39:51 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_proceed_macho(t_generic_file *gen, int argc)
{
	ft_printf("%s:\nContents of (__TEXT,__text) section\n", gen->file_name);
	gen->header = gen->file_start;
	ft_find_texttext_section(gen->header);
	return (NULL);
}

void				ft_find_texttext_section(t_mach_header_64 *header)
{
	t_load_command	*load_command;
	uint32_t		ncmds;

	ncmds = 0;
	load_command = (t_load_command*)((char*)header + sizeof(t_mach_header_64));
	while (ncmds < header->ncmds)
	{
		ft_iter_texttext_sections(load_command, header, &ncmds);
		load_command = (t_load_command*)((char*)load_command
			+ load_command->cmdsize);
		ncmds++;
	}
}

void				ft_iter_texttext_sections(t_load_command *load_command,
	t_mach_header_64 *header, uint32_t *ncmds)
{
	uint32_t		nsects;
	t_section_64	*section;
	void			*content;

	nsects = 0;
	section = (t_section_64*)((char*)load_command
		+ sizeof(t_segment_command_64));
	while (nsects < ((struct segment_command*)load_command)->nsects
		&& ft_strcmp(section->sectname, "__text")
		&& ft_strcmp(section->segname, "__TEXT"))
	{
		section = (t_section_64*)((char*)section + sizeof(t_section_64));
		nsects++;
	}
	if (!ft_strcmp(section->sectname, "__text")
		&& !ft_strcmp(section->segname, "__TEXT"))
	{
		content = (char*)header + section->offset;
		ft_dump_mem(content, section->size, 16, header);
		*ncmds = header->ncmds;
	}
}

void				ft_find_texttext_static_library(void *file_content,
	char *argv)
{
	struct ranlib	*ranlib;
	long int		ranlibs_size;
	t_lib_symbol	*list;
	t_lib_symbol	*ptr;

	ranlibs_size = ((t_static_lib*)file_content)->ranlibs_size;
	ranlib = (struct ranlib*)((char*)file_content + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		ft_find_ranlib_symbols(file_content, ranlib, &list);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib));
		ranlibs_size -= sizeof(struct ranlib);
	}
	ptr = list;
	while (ptr)
	{
		ft_printf("%s(%s):\nContents of (__TEXT,__text) section\n",
			argv, ptr->file_object_name);
		ft_find_texttext_section(ptr->file_object);
		ptr = ptr->next;
	}
	ft_free_static_library_symbols(list);
}

void				*ft_find_ranlib_symbols(void *file_content,
	struct ranlib *ranlib, t_lib_symbol **list)
{
	t_static_lib	*file_object_header_line;
	void			*file_object;
	char			*file_object_name;
	char			*symbol_name;

	symbol_name = (char*)file_content + sizeof(t_static_lib)
		+ ((t_static_lib*)file_content)->ranlibs_size + ranlib->ran_off;
	file_object_header_line = (t_static_lib*)((char*)file_content
		+ (ranlib->ran_un).ran_strx);
	file_object = (char*)file_object_header_line
		+ ft_calculate_distance_file_object(file_object_header_line);
	file_object_name = (char*)file_content
		+ sizeof(((t_static_lib*)file_content)->file_identifier)
		+ (ranlib->ran_un).ran_strx;
	ft_list_lib_symbols(list, symbol_name, file_object_name, file_object);
	return (file_object);
}

int					ft_calculate_distance_file_object(t_static_lib *start_obj)
{
	int				diff;
	int				distance;

	diff = (char*)start_obj->end_identifier
		+ ft_strlen(start_obj->end_identifier)
		- (char*)start_obj;
	distance = ((diff / 8) + 1) * 8;
	distance = diff % 8 > 4 ? distance + 8 : distance;
	return (distance);
}
