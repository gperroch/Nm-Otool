/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterate_fat_arch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:42:35 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/22 17:19:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_iterate_fat_arch(t_generic_file *gen, uint32_t i,
	int onlyone)
{
	uint64_t			offset;
	void				*fat_arch;
	int					argc;

	fat_arch = (char*)(gen->fat_header) + sizeof(struct fat_header)
		+ i * ft_arch_gateway(gen->arch, FAT_ARCH);
	if (!ft_bounds_security(gen, fat_arch))
	{
		ft_errors(CORRUPTED, gen->file_name);
		exit(1);
	}
	ft_arch_title(gen, onlyone, fat_arch);
	offset = gen->arch == 32 ? ((struct fat_arch*)fat_arch)->offset
		: ((struct fat_arch_64*)fat_arch)->offset;
	if (gen->endian_fat == LITTLEEND)
		offset = ft_swap_endian_32bit(offset); // Attention a l'endianness, peut differer entre le fat_header et entre les mach_header
	gen->header = (t_mach_header_64 *)((char*)(gen->fat_header) + offset);
	if (!ft_bounds_security(gen, gen->header))
		return ;
	if (gen->header->magic == MH_CIGAM || gen->header->magic == MH_CIGAM_64)
		gen->endian_mach = BIGEND;
	else if (gen->header->magic == MH_MAGIC
		|| gen->header->magic == MH_MAGIC_64)
		gen->endian_mach = LITTLEEND;
	argc = onlyone ? 2 : -1;
	ft_analyse_file(gen->header, argc, gen->file_name,
		(gen->file_size - (gen->header - (t_mach_header_64 *)gen->file_start))); // Gerer argc
}
