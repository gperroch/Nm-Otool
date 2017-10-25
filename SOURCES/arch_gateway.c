/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_gateway.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:40:05 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/25 16:49:15 by gperroch         ###   ########.fr       */
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

void					ft_fat_arch(void *file_content, char *file_name, unsigned int magic, off_t file_size)
{
	struct fat_header	*fat_header;
	void				*fat_arch;
	uint32_t			i;
	uint64_t			offset;
	int					arch;
	uint32_t			nfat_arch;

	(void)file_name;
	fat_header = file_content;
	ft_printf("OK1\n");
	arch = magic == FAT_MAGIC || magic == FAT_CIGAM ? 32 : 64;
	i = 0;
	fat_arch = (char*)fat_header + sizeof(struct fat_header);
	ft_printf("OK2\n");
	nfat_arch = ft_swap_endian_32bit(fat_header->nfat_arch);
	while (i < nfat_arch)
	{
		offset = arch == 32 ? ((struct fat_arch*)fat_arch)->offset : ((struct fat_arch_64*)fat_arch)->offset;
		offset = ft_swap_endian_32bit(offset);
		ft_printf("OK3 arch:%d nfat_arch:%x offset:%d sizeof(fat_header->nfat_arch):%d\n", arch, nfat_arch, offset, sizeof(fat_header->nfat_arch));
		ft_iterate_fat_arch(file_content, offset, arch, file_size);
		ft_printf("OK4\n");
		fat_arch = (char*)fat_arch + ft_arch_gateway(arch, FAT_ARCH);
		ft_printf("OK5\n");
		i++;
	}
	ft_printf("OK6\n");
}

void					ft_iterate_fat_arch(void *file_content, uint64_t offset, int arch, off_t file_size)
{
	t_generic_file		gen;

	gen.arch = arch;
	gen.header = (t_mach_header_64 *)((char*)file_content + offset);
	dump_mem(gen.header, 16 * 5, 16, "iterate");
	ft_printf("OK3A\n");
	/* RETOURNER TOUT LE FICHIER. A REMONTER DANS LA FONCTION FT_FAT_ARCH SI CA MARCHE */
	int		i = 0;
	char	*file_dump = (char*)malloc(file_size);
	while (i < file_size - 3)
	{
		file_dump[i + 3] = ft_swap_endian_32bit(((char*)file_content)[i]);
		i += 4;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	ft_find_symtab(&gen, 1);
	ft_printf("OK3B\n");
}

int						ft_swap_endian_32bit(int nbr)
{
	int					swapped;

	swapped =	((nbr>>24)&0xff) | // move byte 3 to byte 0
				((nbr<<8)&0xff0000) | // move byte 1 to byte 2
				((nbr>>8)&0xff00) | // move byte 2 to byte 1
				((nbr<<24)&0xff000000); // byte 0 to byte 3
	return (swapped);
}
