/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatDescriber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:35:17 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 12:49:38 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mach-o/ranlib.h>
# include <mach/machine.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "libft.h"
# include "nm_otool.h"

int		main(int argc, char** argv)
{
	char				*file_name;
	int					file_number;
	void				*file_content;
	struct stat			stats;
	int					mapping_result;

	file_name = argv[1];
	if ((mapping_result = ft_mapping_file(file_name, &file_content, &stats)) > 0)
		ft_analyse_file(file_content);
	else
		printf("fatDescriber: %s %s\n\n", file_name, "An error occured.");

	munmap(file_content, stats.st_size);
	return (0);
}

void				ft_analyse_file(void *file_content)
{
	printf("OK.\n");
	struct fat_header	*fatHeader;
 	union FatArch 		fatArch;

	uint32_t			numberArch;
	uint32_t			count;
	uint32_t			sizeFatArch;

	/// FAT HEADER ///

	fatHeader = file_content;
	numberArch = fatHeader->nfat_arch;
	if (fatHeader->magic == FAT_MAGIC)
		printf("32bit Big-endian\n");
	else if (fatHeader->magic == FAT_CIGAM)
		printf("32bit Little-endian\n");
	else if (fatHeader->magic == FAT_MAGIC_64)
		printf("64bit Big-endian\n");
	else if (fatHeader->magic == FAT_CIGAM_64)
		printf("64bit Little-endian\n");
	else
	{
		printf("Not a FAT file. Exit.\n");
		return;
	}

	if (fatHeader->magic == FAT_CIGAM || fatHeader->magic == FAT_CIGAM_64) // Fichier fat en little-endian, passe le nfat_arch de little a big
		numberArch = bigtolittle32(fatHeader->nfat_arch);
	if (fatHeader->magic == FAT_CIGAM || fatHeader->magic == FAT_MAGIC)
		sizeFatArch = sizeof(struct fat_arch);
	else
		sizeFatArch = sizeof(struct fat_arch_64);
	printf("magic = %x, nfat_arch = %u\n", fatHeader->magic, numberArch);

	/// FAT ARCH ///
	count = 1;

	while (count <= numberArch)
	{
		fatArch.fatArch32 = (struct fat_arch*)((char*)fatHeader + sizeof(fatHeader) + (count - 1) * sizeFatArch);
		printf("cputype = %d, cpusubtype = %d, offset = %u, size = %u, align = %u\n", bigtolittle64(fatArch.fatArch32->cputype), bigtolittle64(fatArch.fatArch32->cpusubtype),
		bigtolittle32(fatArch.fatArch32->offset), bigtolittle32(fatArch.fatArch32->size), bigtolittle32(fatArch.fatArch32->align));
		ft_describe_arch(file_content, bigtolittle32(fatArch.fatArch32->offset));
		count++;
	}
}

void			ft_describe_arch(void *file_content, uint32_t offset)
{
	void 		*arch;

	arch = (char*)file_content + offset;
	dump_mem(arch, 6 * 32, 32, arch);
}

uint32_t		bigtolittle32(uint32_t n)
{
	uint32_t	res;
	res = ((n>>24)&0xff) | // move byte 3 to byte 0
		((n<<8)&0xff0000) | // move byte 1 to byte 2
		((n>>8)&0xff00) | // move byte 2 to byte 1
		((n<<24)&0xff000000); // byte 0 to byte 3

	return res;
}

uint64_t		bigtolittle64(uint64_t n)
{
	uint64_t	res;
	res = ((n>>56)&0xff) |
		((n<<56)&0xff00000000000000) |
		((n>>40)&0xff00) |
		((n<<40)&0xff000000000000) |
		((n>>24)&0xff0000) |
		((n<<24)&0xff0000000000) |
		((n<<8)&0xff000000) |
		((n>>8)&0xff00000000);

	return res;
}
