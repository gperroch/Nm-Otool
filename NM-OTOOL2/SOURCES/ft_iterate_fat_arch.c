/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterate_fat_arch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:42:35 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 16:53:20 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_iterate_fat_arch(t_generic_file *gen, uint32_t i, int onlyOne, int otool)
{
	char				*cputype;
	uint64_t			offset;
	void				*fat_arch;

	fat_arch = (char*)(gen->fat_header) + sizeof(struct fat_header) + i * ft_arch_gateway(gen->arch, FAT_ARCH);
	if (!ft_bounds_security(gen, fat_arch))
		return ;
	if (gen->endian_fat == BIGEND)
		cputype = ft_get_arch_type(((struct fat_arch_64*)fat_arch)->cputype);
	else if (gen->endian_fat == LITTLEEND)
		cputype = ft_get_arch_type(ft_swap_endian_32bit(((struct fat_arch_64*)fat_arch)->cputype));
	else
		cputype = ft_strdup("undefined");
	if (!onlyOne && gen->nfat_arch != 1)
		ft_printf("\n%s (for architecture %s):\n", gen->file_name, cputype);
	else if (gen->nfat_arch == 1 && !otool)
		ft_printf("%s:\n", gen->file_name);
	free(cputype);
	offset = gen->arch == 32 ? ((struct fat_arch*)fat_arch)->offset : ((struct fat_arch_64*)fat_arch)->offset;
	if (gen->endian_fat == LITTLEEND)
		offset = ft_swap_endian_32bit(offset); // Attention a l'endianness, peut differer entre le fat_header et entre les mach_header
	gen->header = (t_mach_header_64 *)((char*)(gen->fat_header) + offset);
	if (!ft_bounds_security(gen, gen->header))
		return ;
	if (gen->header->magic == MH_CIGAM || gen->header->magic == MH_CIGAM_64)
		gen->endian_mach = BIGEND;
	else if (gen->header->magic == MH_MAGIC || gen->header->magic == MH_MAGIC_64)
		gen->endian_mach = LITTLEEND;
	ft_analyse_file(gen->header, 2, gen->file_name, (gen->file_size - (gen->header - (t_mach_header_64 *)gen->file_start))); // Gerer argc
	//ft_find_symtab(gen, 1);
}
