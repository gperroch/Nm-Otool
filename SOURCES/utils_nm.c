/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:52:12 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/19 18:42:19 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
void				ft_free_list_symbols(t_symbol_display *list);

t_symbol_display			*ft_find_symtab(t_mach_header_64 *header,
	char to_display)
{
	t_symtab_command		*symtab_command;
	void					*symtab;
	void					*strtab;
	t_symbol_display		*list;

	ft_locate_symbol_table(header, &symtab, &strtab, &symtab_command);
	list = ft_create_symbol_list(symtab, strtab, symtab_command, header);
	ft_sort_list_symbols(&list);
	if (to_display)
	{
		ft_display_symbols(list);
		ft_free_list_symbols(list);
	}
	return (list);
}

void						ft_locate_symbol_table(t_mach_header_64 *header,
	void **symtab, void **strtab, t_symtab_command **symtab_command)
{
	t_load_command			*load_command;
	uint32_t				lc_counter;

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
	void					*section;
	int						section_counter;

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

char						ft_section_type(t_section_64 *section)
{
	char					res;

	res = 'S';
	res = !ft_strcmp(section->sectname, "__text") ? 'T' : res;
	res = !ft_strcmp(section->sectname, "__data") ? 'D' : res;
	res = !ft_strcmp(section->sectname, "__bss") ? 'B' : res;
	res = !ft_strcmp(section->sectname, "__common") &&
			ft_strcmp(section->segname, "__DATA") ? 'C' : res;
	return (res);
}
