/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locate_symbol_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:01:38 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 13:19:42 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						ft_locate_symbol_table(t_generic_file *gen,
	void **symtab, void **strtab, t_symtab_command **symtab_command)
{
	uint32_t				lc_max;

	lc_max = gen->endian_mach == LITTLEEND ?
		ft_swap_endian_32bit(gen->header->ncmds) : gen->header->ncmds;
	if (!(*symtab_command =
		(t_symtab_command*)ft_locate_symtab_command(lc_max, gen)))
	{
		ft_errors(CORRUPTED, gen->file_name);
		exit(1);
	}
	*symtab = (char*)(gen->header);
	*strtab = (char*)(gen->header);
	*symtab += gen->endian_mach == LITTLEEND ? ft_swap_endian_32bit(
		(*symtab_command)->symoff) : (*symtab_command)->symoff;
	*strtab += gen->endian_mach == LITTLEEND ? ft_swap_endian_32bit(
		(*symtab_command)->stroff) : (*symtab_command)->stroff;
}
