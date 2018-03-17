/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:36:04 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 17:10:45 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char						ft_find_section(t_generic_file *gen)
{
	t_load_command			*load_cmd;
	void					*segment_command;
	void					*section;
	int						section_counter;
	uint32_t	nsects;

	section_counter = 0;
	load_cmd = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER));
	while (section_counter < gen->n_sect)
	{
		if (!ft_bounds_security(gen, load_cmd))
			return (0);

		nsects = ((t_segment_command_64*)load_cmd)->nsects;
		if (gen->arch == 32)
			nsects = ((t_segment_command*)load_cmd)->nsects;
		if (gen->endian_mach == LITTLEEND)
			nsects = ft_swap_endian_32bit(nsects);



		if ((gen->endian_mach == LITTLEEND && ft_swap_endian_32bit(load_cmd->cmd) == LC_SEGMENT) || (gen->endian_mach == BIGEND && load_cmd->cmd == LC_SEGMENT)) // Les swap ne sont pas pour le big mais le little
			section_counter += nsects;
		else if ((gen->endian_mach == LITTLEEND && ft_swap_endian_32bit(load_cmd->cmd) == LC_SEGMENT_64) || (gen->endian_mach == BIGEND && load_cmd->cmd == LC_SEGMENT_64))
			section_counter += nsects;
		if (section_counter < gen->n_sect && gen->endian_mach == LITTLEEND)
			load_cmd = (t_load_command*)((char*)load_cmd + ft_swap_endian_32bit(load_cmd->cmdsize));
		else if (section_counter < gen->n_sect && gen->endian_mach == BIGEND)
			load_cmd = (t_load_command*)((char*)load_cmd + load_cmd->cmdsize);
	}
	if (!ft_bounds_security(gen, load_cmd))
		return (0);

	uint32_t	cmd;
	//uint32_t	nsects;
	cmd = load_cmd->cmd;
	nsects = ((t_segment_command_64*)load_cmd)->nsects;
	if (gen->arch == 32)
		nsects = ((t_segment_command*)load_cmd)->nsects;
	if (gen->endian_mach == LITTLEEND)
	{
		nsects = ft_swap_endian_32bit(nsects);
		cmd = ft_swap_endian_32bit(cmd);
	}

	if (cmd == LC_SEGMENT)
		section_counter -= (nsects - 1);
	else if (cmd == LC_SEGMENT_64)
		section_counter -= (nsects - 1); // t_segment_command_64 !!!
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
