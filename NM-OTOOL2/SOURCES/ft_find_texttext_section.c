/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_texttext_section.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:00:45 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 17:37:48 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

//void				ft_find_texttext_section(t_mach_header_64 *header, int arch)
void				ft_find_texttext_section(t_generic_file *gen)
{
	t_load_command	*load_command;
	uint32_t		ncmds;
	uint32_t		ncmdsMax;
	int				size_mach_header;

	ncmds = 0;
	if (gen->arch == 32)
		size_mach_header = sizeof(t_mach_header);
	else
		size_mach_header = sizeof(t_mach_header_64);
	load_command = (t_load_command*)((char*)(gen->header) + size_mach_header);
	ncmdsMax = gen->header->ncmds;
	if (gen->endian_mach == LITTLEEND)
		ncmdsMax = ft_swap_endian_32bit(ncmdsMax);
	while (ncmds < ncmdsMax)
	{
//		ft_printf("header->ncmds[%d] [%d]\n", ncmds, ncmdsMax);
		ft_iter_texttext_sections(load_command, &ncmds, gen);
		if (gen->endian_mach == LITTLEEND)
			load_command = (t_load_command*)((char*)load_command + ft_swap_endian_32bit(load_command->cmdsize));
		else
			load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
		ncmds++;
	}
}
