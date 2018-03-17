/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_texttext_section.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:00:45 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 16:50:44 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_find_texttext_section(t_generic_file *gen)
{
	t_load_command	*load_command;
	uint32_t		ncmds;
	uint32_t		ncmdsmax;
	int				size_mach_header;

	ncmds = -1;
	size_mach_header = sizeof(t_mach_header_64);
	if (gen->arch == 32)
		size_mach_header = sizeof(t_mach_header);
	load_command = (t_load_command*)((char*)(gen->header) + size_mach_header);
	ncmdsmax = gen->header->ncmds;
	if (gen->endian_mach == LITTLEEND)
		ncmdsmax = ft_swap_endian_32bit(ncmdsmax);
	while (++ncmds < ncmdsmax)
	{
		ft_iter_texttext_sections(load_command, &ncmds, gen);
		if (gen->endian_mach == LITTLEEND)
			load_command = (t_load_command*)((char*)load_command
			+ ft_swap_endian_32bit(load_command->cmdsize));
		else
			load_command = (t_load_command*)((char*)load_command
			+ load_command->cmdsize);
	}
}
