/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_gateway.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:40:05 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 14:26:57 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int			ft_arch_gateway(int arch, int element)
{
	int		ret;

	if (arch != 32 && arch != 64)
		return (-1);
	if (element == MACH_HEADER)
		ret = arch == 32 ? SIZE_MACH_HEADER_32 : SIZE_MACH_HEADER_64;
	else if (element == SEGMENT_COMMAND)
		ret = arch == 32 ? SIZE_SEGMENT_COMMAND_32 : SIZE_SEGMENT_COMMAND_64;
	else if (element == SECTION)
		ret = arch == 32 ? SIZE_SECTION_32 : SIZE_SECTION_64;
	else if (element == FAT_ARCH)
		ret = arch == 32 ? SIZE_FAT_ARCH_32 : SIZE_FAT_ARCH_64;
	else
		ret = -2;
	return (ret);
}

void					ft_fat_arch(void *file_content, char *file_name,
	unsigned int magic, off_t file_size)
{
	uint32_t			i;
	t_generic_file		gen;

	i = -1;
	gen.arch = magic == FAT_MAGIC || magic == FAT_CIGAM ? 32 : 64;
	gen.file_size = file_size;
	gen.file_name = file_name;
	gen.fat_header = file_content;
	gen.file_start = file_content;
	if (magic == FAT_CIGAM || magic == FAT_CIGAM_64)
	{
		gen.endian_fat = BIGEND;
		gen.nfat_arch = ft_swap_endian_32bit(gen.fat_header->nfat_arch);
	}
	else if (magic == FAT_MAGIC || magic == FAT_MAGIC_64)
	{
		gen.endian_fat = LITTLEEND;
		gen.nfat_arch = gen.fat_header->nfat_arch;
	}
	else
		return ; // Message d'erreur
	while (++i < gen.nfat_arch)
		ft_iterate_fat_arch(&gen, i);
}


void					ft_iterate_fat_arch(t_generic_file *gen, uint32_t i)
{
	char				*cputype;
	uint64_t			offset;
	void				*fat_arch;

	fat_arch = (char*)(gen->fat_header) + sizeof(struct fat_header) + i * ft_arch_gateway(gen->arch, FAT_ARCH);
	if (!ft_bounds_security(gen, fat_arch))
		return ;
	if (gen->endian_fat == BIGEND)
		cputype = ft_get_arch_type(ft_swap_endian_32bit(((struct fat_arch_64*)fat_arch)->cputype));
	else if (gen->endian_fat == LITTLEEND)
		cputype = ft_get_arch_type(((struct fat_arch_64*)fat_arch)->cputype);
	else
		cputype = ft_strdup("undefined");
	ft_printf("\n%s (for architecture %s):\n", gen->file_name, cputype);
	free(cputype);
	offset = gen->arch == 32 ? ((struct fat_arch*)fat_arch)->offset : ((struct fat_arch_64*)fat_arch)->offset;
	if (gen->endian_fat == BIGEND)
		offset = ft_swap_endian_32bit(offset); // Attention a l'endianness, peut differer entre le fat_header et entre les mach_header
	gen->header = (t_mach_header_64 *)((char*)(gen->fat_header) + offset);
	if (!ft_bounds_security(gen, gen->header))
		return ;
	if (gen->header->magic == MH_CIGAM || gen->header->magic == MH_CIGAM_64)
		gen->endian_mach = BIGEND;
	else if (gen->header->magic == MH_MAGIC || gen->header->magic == MH_MAGIC_64)
		gen->endian_mach = LITTLEEND;
	ft_find_symtab(gen, 1);
}

int						ft_swap_endian_32bit(int nbr) // ATTENTION AUX NOMBRES DANS LES NOMS DE FONCTION
{
	int					swapped;

	swapped =	((nbr>>24)&0xff) | // move byte 3 to byte 0
				((nbr<<8)&0xff0000) | // move byte 1 to byte 2
				((nbr>>8)&0xff00) | // move byte 2 to byte 1
				((nbr<<24)&0xff000000); // byte 0 to byte 3
	return (swapped);
}

char					*ft_get_arch_type(int cputype) // Traiter tous les types et sous-types. Tester avec d'autres cputype et cpusubtype
{
	char				*str;

	if (cputype == CPU_TYPE_X86)
		str = ft_strdup("i386");
	else if (cputype == CPU_TYPE_X86_64)
		str = ft_strdup("x86_64");
	else if (cputype == CPU_TYPE_POWERPC)
		str = ft_strdup("ppc");
	else
		str = ft_strdup("undefined");
	return (str);
}

int							ft_bounds_security(t_generic_file *gen, void *ptr)
{
	void					*max_addr;

	max_addr = (char*)(gen->file_start) + gen->file_size;
	if ((char*)ptr - (char*)max_addr > 0)
	{
		ft_printf("ft_nm: %s truncated or malformed object max_addr[%p] ptr[%p]\n\n", gen->file_name, max_addr, ptr);
		return (0);
	}
	return (1);
}
