/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locate_symbol_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:01:38 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 14:32:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						ft_locate_symbol_table(t_generic_file *gen, void **symtab, void **strtab, t_symtab_command **symtab_command) // GATEWAY // UTILISER DE MANIERE REGULIERE
{
	t_load_command			*load_command;
	uint32_t				lc_counter;
	uint32_t				lc_max;
	uint32_t				cmdsize;

	lc_counter = 0;
	load_command = (t_load_command*)((char*)(gen->header) + ft_arch_gateway(gen->arch, MACH_HEADER)); // GATEWAY
	if (gen->endian_mach == LITTLEEND)	// ternaire
		lc_max = ft_swap_endian_32bit(gen->header->ncmds);
	else
		lc_max = gen->header->ncmds;


	while (lc_counter < lc_max)
	{
		if (gen->endian_mach == LITTLEEND)
			cmdsize = ft_swap_endian_32bit(load_command->cmdsize);
		else
			cmdsize = load_command->cmdsize;
		load_command = (t_load_command*)((char*)load_command + cmdsize);
		lc_counter++;
/*		if (!ft_bounds_security(gen, load_command)) // Necessite gen.file_size et gen.file_start pour fonctionner
			return ;*/
		if (load_command->cmd == LC_SYMTAB)
			lc_counter = lc_max;
	}
	*symtab_command = (t_symtab_command*)load_command;

	if (gen->endian_mach == LITTLEEND) // ternaire
	{
		*symtab = (char*)(gen->header) + ft_swap_endian_32bit((*symtab_command)->symoff);
		*strtab = (char*)(gen->header) + ft_swap_endian_32bit((*symtab_command)->stroff);
	}
	else
	{
		*symtab = (char*)(gen->header) + (*symtab_command)->symoff;
		*strtab = (char*)(gen->header) + (*symtab_command)->stroff;
	}
}
