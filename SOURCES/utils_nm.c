/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:52:12 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/27 17:50:21 by gperroch         ###   ########.fr       */
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

	if (gen->file_start == NULL)
		gen->file_start = gen->header;
	if (gen->endian_mach == LITTLEEND)
	{
		ft_locate_symbol_table(gen, &symtab, &strtab, &symtab_command); // GATEWAY
		list = ft_create_symbol_list(symtab, strtab, symtab_command, gen); // !!!
		ft_printf("LIST[%p]\n", list);
	}
	else if (gen->endian_mach == BIGEND) // GERER ca pour d'autre architectures que FAT
	{
		ft_locate_symbol_table_bigendian(gen, &symtab, &strtab, &symtab_command); // GATEWAY
		list = ft_create_symbol_list_bigendian(symtab, strtab, symtab_command, gen); // !!!
	}
	//list = ft_create_symbol_list(symtab, strtab, symtab_command, gen); // !!! // 64bit originel
	ft_sort_list_symbols(&list);
	if (to_display)
	{
		ft_display_symbols(list, gen);
		ft_free_list_symbols(list);
	}
	return (list);
}

void						ft_locate_symbol_table_bigendian(t_generic_file *gen, void **symtab, void **strtab, t_symtab_command **symtab_command) // GATEWAY
{
	t_load_command			*load_command;
	int				lc_counter;

	lc_counter = 0;
	load_command = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER)); // GATEWAY
	while (lc_counter < ft_swap_endian_32bit(gen->header->ncmds))
	{
		load_command = (t_load_command*)((char*)load_command
			+ ft_swap_endian_32bit(load_command->cmdsize));
		lc_counter++;
		if (!ft_bounds_security(gen, load_command))
			return ;
		if (ft_swap_endian_32bit(load_command->cmd) == LC_SYMTAB)
			lc_counter = ft_swap_endian_32bit(gen->header->ncmds);
	}
	*symtab_command = (t_symtab_command*)load_command;
	*symtab = (char*)(gen->header) + ft_swap_endian_32bit((*symtab_command)->symoff);
	*strtab = (char*)(gen->header) + ft_swap_endian_32bit((*symtab_command)->stroff);
}


void						ft_locate_symbol_table(t_generic_file *gen, void **symtab, void **strtab, t_symtab_command **symtab_command) // GATEWAY // UTILISER DE MANIERE REGULIERE
{
	t_load_command			*load_command;
	uint32_t				lc_counter;

	lc_counter = 0;
	load_command = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER)); // GATEWAY
	while (lc_counter < gen->header->ncmds)
	{
		load_command = (t_load_command*)((char*)load_command
			+ load_command->cmdsize);
		lc_counter++;
		if (!ft_bounds_security(gen, load_command))
			return ;
		if (load_command->cmd == LC_SYMTAB)
			lc_counter = gen->header->ncmds;
	}
	*symtab_command = (t_symtab_command*)load_command;
	*symtab = (char*)(gen->header) + (*symtab_command)->symoff;
	*strtab = (char*)(gen->header) + (*symtab_command)->stroff;
}

char						ft_find_section_bigendian(t_generic_file *gen)
{
	t_load_command			*load_cmd;
	void					*segment_command;
	void					*section;
	int						section_counter;

	section_counter = 0;
	load_cmd = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER)); // GATEWAY
	while (section_counter < gen->n_sect)
	{
		if (!ft_bounds_security(gen, load_cmd))
			return (0);
		if (ft_swap_endian_32bit(load_cmd->cmd) == LC_SEGMENT)
			section_counter += ((t_segment_command*)load_cmd)->nsects;
		else if (ft_swap_endian_32bit(load_cmd->cmd) == LC_SEGMENT_64)
			section_counter += ((t_segment_command_64*)load_cmd)->nsects;
		if (section_counter < gen->n_sect)
		{
			load_cmd = (t_load_command*)((char*)load_cmd + ft_swap_endian_32bit(load_cmd->cmdsize));
		}
	}
	if (!ft_bounds_security(gen, load_cmd))
		return (0);
	if (load_cmd->cmd == LC_SEGMENT)
		section_counter -= (((t_segment_command*)load_cmd)->nsects - 1); // !!!
	else if (load_cmd->cmd == LC_SEGMENT_64)
		section_counter -= (((t_segment_command_64*)load_cmd)->nsects - 1); // t_segment_command_64 !!!
	segment_command = load_cmd;
	section = (char*)segment_command + ft_arch_gateway(gen->arch, SEGMENT_COMMAND);//sizeof(t_segment_command_64);
	while (section_counter < gen->n_sect)
	{
		section = (char*)section + ft_arch_gateway(gen->arch, SECTION);//sizeof(t_section_64);
		if (!ft_bounds_security(gen, section))
			return (0);
		section_counter++;
	}
	return (ft_section_type(section));
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
	load_cmd = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER)); // GATEWAY
	ft_printf("magic:[%x]\n", gen->header->magic);
	dump_mem(gen->header, sizeof(struct mach_header_64), sizeof(struct mach_header_64), "mach");
	dump_mem(load_cmd, sizeof(struct load_command), sizeof(struct load_command), "load");
	while (section_counter < gen->n_sect)
	{
		//ft_printf("OK1 section_counter[%6d] gen->n_sect[%6d] load_command[%10p] load_command->cmd[%6d]\n", section_counter, gen->n_sect, load_cmd, load_cmd->cmd);
		if (!ft_bounds_security(gen, load_cmd))
			return (0);
		if (load_cmd->cmd == LC_SEGMENT)
			section_counter += ((t_segment_command*)load_cmd)->nsects;
		else if (load_cmd->cmd == LC_SEGMENT_64)
			section_counter += ((t_segment_command_64*)load_cmd)->nsects;
		if (section_counter < gen->n_sect)
			load_cmd = (t_load_command*)((char*)load_cmd + load_cmd->cmdsize);
	}
	if (!ft_bounds_security(gen, load_cmd))
		return (0);
	if (load_cmd->cmd == LC_SEGMENT)
		section_counter -= (((t_segment_command*)load_cmd)->nsects - 1); // !!!
	else if (load_cmd->cmd == LC_SEGMENT_64)
		section_counter -= (((t_segment_command_64*)load_cmd)->nsects - 1); // t_segment_command_64 !!!
	segment_command = load_cmd;
	section = (char*)segment_command + ft_arch_gateway(gen->arch, SEGMENT_COMMAND);//sizeof(t_segment_command_64);
	while (section_counter < gen->n_sect)
	{
		section = (char*)section + ft_arch_gateway(gen->arch, SECTION);//sizeof(t_section_64);
		if (!ft_bounds_security(gen, section))
			return (0);
		section_counter++;
	}
	return (ft_section_type(section));
}

char						ft_section_type(t_section_64 *section)
{
	char					res;

	if (!ft_has_print(section->sectname))
		return (0);
	res = 'S';
	res = !ft_strcmp(section->sectname, "__text") ? 'T' : res;
	res = !ft_strcmp(section->sectname, "__data") ? 'D' : res;
	res = !ft_strcmp(section->sectname, "__bss") ? 'B' : res;
	res = !ft_strcmp(section->sectname, "__common") &&
			ft_strcmp(section->segname, "__DATA") ? 'C' : res;
	return (res);
}

int						ft_has_print(char *str)
{
	char				has_print;
	int					len;

	has_print = 0;
	len = ft_strlen(str);
	while (len > 0)
	{
		if (ft_isprint(str[len - 1]))
			has_print = 1;
		len--;
	}
	return (has_print);
}
