/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_gateway.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:40:05 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/25 18:10:39 by gperroch         ###   ########.fr       */
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
	//struct fat_header	*fat_header;
	void				*fat_arch;
	uint32_t			i;
	uint64_t			offset;
	//int					arch;
	//uint32_t			nfat_arch;
	t_generic_file		gen;

	(void)file_name;
	if (magic == FAT_CIGAM || magic == FAT_CIGAM_64)
		gen.endian = BIGEND;
	else
		gen.endian = LITTLEEND;
	gen.arch = magic == FAT_MAGIC || magic == FAT_CIGAM ? 32 : 64;
	gen.file_size = file_size;

	gen.fat_header = file_content;
	ft_printf("OK1\n");
	i = 0;
	fat_arch = (char*)(gen.fat_header) + sizeof(struct fat_header);
	//ft_printf("OK2\n");
	//gen.nfat_arch = (gen.fat_header)->nfat_arch;
	gen.nfat_arch = ft_swap_endian_32bit(gen.fat_header->nfat_arch);
	//nfat_arch = ft_revert_endianness_4bytes(fat_header->nfat_arch);
	while (i < gen.nfat_arch)
	{
		offset = gen.arch == 32 ? ((struct fat_arch*)fat_arch)->offset : ((struct fat_arch_64*)fat_arch)->offset;
		offset = ft_swap_endian_32bit(offset);
		ft_printf("OK3 arch:%d nfat_arch:%x offset:%d sizeof(fat_header->nfat_arch):%d\n", gen.arch, gen.nfat_arch, offset, sizeof(gen.fat_header->nfat_arch));
		ft_iterate_fat_arch(&gen, offset);
		ft_printf("OK4\n");
		fat_arch = (char*)fat_arch + ft_arch_gateway(gen.arch, FAT_ARCH);
		ft_printf("OK5\n");
		i++;
	}
	ft_printf("OK6\n");
}

void					ft_iterate_fat_arch(t_generic_file *gen, uint64_t offset)
{
	gen->header = (t_mach_header_64 *)((char*)(gen->fat_header) + offset);
	//dump_mem(gen.header, 16 * 5, 16, "iterate");
	/* CHANGER L'ENDIANNESS DU FICHIER */ // A FAIRE AU CAS PAR CAS
/*	char		*file_copy;
	ft_printf("content:[%x]\n", ((struct fat_header*)file_content)->magic);
	file_copy = ft_revert_endianness_4bytes(file_content, file_size);
	ft_printf("copy after:[%x] [%d/%x]\n", ((struct fat_header*)file_copy)->magic, ((struct fat_header*)file_copy)->nfat_arch);
	dump_mem(file_copy, 16*5, 16, "copy");
	dump_mem(file_content, 16*5, 16, "content"); */
	/////////////////////////////////////
	ft_printf("OK3A\n");
	ft_find_symtab(gen, 1);
	ft_printf("OK3B\n");
}

int						ft_revert_endianness_4bytes(int nbr) // Merdique. Utiliser l'autre
{
	char				*file_copy;
	char				tmp;

	file_copy = (char*)(&nbr);
	tmp = file_copy[3];
	file_copy[3] = file_copy[0];
	file_copy[0] = tmp;
	tmp = file_copy[2];
	file_copy[2] = file_copy[1];
	file_copy[1] = tmp;

	return (*file_copy);
}

void					*ft_revert_endianness_4bytes_full(void *file_content, off_t file_size) // ATTENTION AUX NOMBRES DANS LES NOMS DE FONCTION
{
	/* VERSION FICHIER COMPLET */
	char				*file_copy;
	char				tmp;
	int					i = 0;

	file_copy = (char*)malloc(file_size);
	ft_memcpy(file_copy, file_content, file_size);
	ft_printf("copy before:[%x] [%d/%x]\n", ((struct fat_header*)file_copy)->magic, ((struct fat_header*)file_copy)->nfat_arch);
	while (i < file_size - 3)
	{
		tmp = file_copy[i + 3];
		file_copy[i + 3] = file_copy[i + 0];
		file_copy[i + 0] = tmp;
		tmp = file_copy[i + 2];
		file_copy[i + 2] = file_copy[i + 1];
		file_copy[i + 1] = tmp;
		i += 4;
	}
	return (file_copy);
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
