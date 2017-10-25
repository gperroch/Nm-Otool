/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:52:12 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/25 13:51:37 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
/* VERSION 64bit
t_symbol_display			*ft_find_symtab(t_mach_header_64 *header, char to_display) // 64bit
{
	t_symtab_command		*symtab_command;
	void					*symtab;
	void					*strtab;
	t_symbol_display		*list;

	ft_printf("OK1\n");
	ft_locate_symbol_table(header, &symtab, &strtab, &symtab_command); // 64bit
	ft_printf("OK2\n");
	list = ft_create_symbol_list(symtab, strtab, symtab_command, header);
	ft_printf("OK3\n");
	ft_sort_list_symbols(&list);
	ft_printf("OK4\n");
	if (to_display)
	{
		ft_display_symbols(list);
		ft_free_list_symbols(list);
	}
	return (list);
}

void						ft_locate_symbol_table(t_mach_header_64 *header, void **symtab, void **strtab, t_symtab_command **symtab_command) // 64bit
{
	t_load_command			*load_command;
	uint32_t				lc_counter;

	lc_counter = 0;
	ft_printf("OK1A\n");
	// Premier segfault en 32bit. Changer le type t_mach_header_64, ou le type de sizeof(header)
	load_command = (t_load_command*)((char*)header + sizeof(t_mach_header_64)); // 64bit
	ft_printf("OK1B\n");
	while (lc_counter < header->ncmds)
	{
		load_command = (t_load_command*)((char*)load_command
			+ load_command->cmdsize);
		lc_counter++;
		if (load_command->cmd == LC_SYMTAB)
			lc_counter = header->ncmds;
	}
	ft_printf("OK1C\n");
	*symtab_command = (t_symtab_command*)load_command;
	ft_printf("OK1D\n");
	*symtab = (char*)header + (*symtab_command)->symoff;
	ft_printf("OK1E\n");
	*strtab = (char*)header + (*symtab_command)->stroff;
	ft_printf("OK1F\n");
}

char						ft_find_section(void *header, int section_number)
{
	t_load_command			*load_cmd;
	t_segment_command_64	*segment_command;
	void					*section;
	int						section_counter;

	section_counter = 0;
	load_cmd = (t_load_command*)((char*)header + sizeof(t_mach_header_64)); // 64bit
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
*/





/* VERSION GATEWAY */
t_symbol_display			*ft_find_symtab(t_generic_file *gen, char to_display) // GATEWAY
{
	t_symtab_command		*symtab_command;
	void					*symtab;
	void					*strtab;
	t_symbol_display		*list;

	ft_printf("OK1 gen->header:%p gen->arch:%d\n", gen->header, gen->arch);
	ft_locate_symbol_table(gen, &symtab, &strtab, &symtab_command); // GATEWAY
	ft_printf("OK2\n");
	list = ft_create_symbol_list(symtab, strtab, symtab_command, gen); // !!!
	ft_printf("OK3\n");
	ft_sort_list_symbols(&list);
	ft_printf("OK4\n");
	if (to_display)
	{
		ft_printf("OK5\n");
		ft_display_symbols(list);
		ft_printf("OK6\n");
		ft_free_list_symbols(list);
		ft_printf("OK7\n");
	}
	return (list);
}

void						ft_locate_symbol_table(t_generic_file *gen, void **symtab, void **strtab, t_symtab_command **symtab_command) // GATEWAY
{
	t_load_command			*load_command;
	uint32_t				lc_counter;

	lc_counter = 0;
	ft_printf("OK1A ft_arch_gateway(gen->arch, MACH_HEADER):%d sizeof(struct mach_header):%d sizeof(struct mach_header_64):%d\n", ft_arch_gateway(gen->arch, MACH_HEADER), sizeof(struct mach_header), sizeof(struct mach_header_64));
	load_command = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER)); // GATEWAY
	ft_printf("OK1B\n");
	while (lc_counter < gen->header->ncmds)
	{
		load_command = (t_load_command*)((char*)load_command
			+ load_command->cmdsize);
		lc_counter++;
		if (load_command->cmd == LC_SYMTAB)
			lc_counter = gen->header->ncmds;
	}
	ft_printf("OK1C\n");
	*symtab_command = (t_symtab_command*)load_command;
	ft_printf("OK1D\n");
	*symtab = (char*)(gen->header) + (*symtab_command)->symoff;
	ft_printf("OK1E\n");
	*strtab = (char*)(gen->header) + (*symtab_command)->stroff;
	ft_printf("OK1F\n");
}

char						ft_find_section(t_generic_file *gen)
{
	t_load_command			*load_cmd;
//	t_segment_command_64	*segment_command; // 64bit
//	t_segment_command		*segment_command; // 32bit
	void					*segment_command;
	void					*section;
	int						section_counter;

	section_counter = 0;
	//load_cmd = (t_load_command*)((char*)header + sizeof(t_mach_header_64)); // 64bit
	//load_cmd = (t_load_command*)((char*)header + sizeof(t_mach_header)); // 32bit
	load_cmd = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER)); // GATEWAY
	while (section_counter < gen->n_sect)
	{
		if (load_cmd->cmd == LC_SEGMENT)
			section_counter += ((t_segment_command*)load_cmd)->nsects;
		else if (load_cmd->cmd == LC_SEGMENT_64)
			section_counter += ((t_segment_command_64*)load_cmd)->nsects;
		if (section_counter < gen->n_sect)
			load_cmd = (t_load_command*)((char*)load_cmd + load_cmd->cmdsize);
	}
	if (load_cmd->cmd == LC_SEGMENT)
		section_counter -= (((t_segment_command*)load_cmd)->nsects - 1); // !!!
	else if (load_cmd->cmd == LC_SEGMENT_64)
		section_counter -= (((t_segment_command_64*)load_cmd)->nsects - 1); // t_segment_command_64 !!!
	segment_command = load_cmd;
	section = (char*)segment_command + ft_arch_gateway(gen->arch, SEGMENT_COMMAND);//sizeof(t_segment_command_64);
	while (section_counter < gen->n_sect)
	{
		section = (char*)section + ft_arch_gateway(gen->arch, SECTION);//sizeof(t_section_64);
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
