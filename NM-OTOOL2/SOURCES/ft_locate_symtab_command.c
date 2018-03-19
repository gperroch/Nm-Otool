/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locate_symtab_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:18:38 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 13:20:16 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				*ft_locate_symtab_command(uint32_t lc_max,
	t_generic_file *gen)
{
	t_load_command	*load_command;
	uint32_t		lc_counter;
	uint32_t		cmdsize;

	lc_counter = 0;
	load_command = (t_load_command*)((char*)(gen->header)
		+ ft_arch_gateway(gen->arch, MACH_HEADER));
	while (lc_counter < lc_max)
	{
		if (gen->endian_mach == LITTLEEND)
			cmdsize = ft_swap_endian_32bit(load_command->cmdsize);
		else
			cmdsize = load_command->cmdsize;
		load_command = (t_load_command*)((char*)load_command + cmdsize);
		lc_counter++;
		if (!ft_bounds_security(gen, load_command))
			return (NULL);
		if ((gen->endian_mach == BIGEND && load_command->cmd == LC_SYMTAB)
			|| (gen->endian_mach == LITTLEEND
			&& ft_swap_endian_32bit(load_command->cmd) == LC_SYMTAB)) // LC_DYSYMTAB ???
			lc_counter = lc_max;
	}
	return (load_command);
}
