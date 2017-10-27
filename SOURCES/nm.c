/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 10:56:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/27 14:36:13 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

// 32-bit ?ok?
// .dylib ?ok?
// Architectures FAT
// Securite segfault sur les fichiers corrompus
// Bonus -p -u -U -j -r
// Big endian et Little endian
// POUR OTOOL AUSSI

static void				ft_analyse_file(void *file_content, char *file_name, int argc, off_t file_size)
{
	//t_mach_header_64	*header;
	char				*file_start;
	t_symbol_display	*list;
	t_generic_file		gen; // GATEWAY

	//header = file_content; // 64bit
	ft_bzero(&gen, sizeof(t_generic_file));
	gen.header = (t_mach_header_64*)file_content; // GATEWAY
	gen.file_start = NULL;
	gen.file_size = file_size;
	gen.file_name = file_name;

	file_start = ft_strncpy(ft_strnew(7), file_content, 7);
	//if (header->magic == 0xfeedfacf || header->magic == 0xfeedface) // 64bit
	if (gen.header->magic == MH_MAGIC || gen.header->magic == MH_MAGIC_64) // GATEWAY // ATTENTION A L'ENDIANNESS ICI AUSSI
	{
		if (argc > 2)
			ft_printf("\n%s:\n", file_name);
		gen.endian_mach = LITTLEEND;
		if (gen.header->magic == MH_CIGAM || gen.header->magic == MH_CIGAM_64)
			gen.endian_mach = BIGEND;
		gen.arch = gen.header->magic == 0xfeedfacf ? 64 : 32;
		//list = ft_find_symtab(header, 1); // 64bit
		list = ft_find_symtab(&gen, 1); // GATEWAY
	}
	else if (((struct fat_header*)file_content)->magic == FAT_MAGIC || ((struct fat_header*)file_content)->magic == FAT_MAGIC_64
		|| ((struct fat_header*)file_content)->magic == FAT_CIGAM || ((struct fat_header*)file_content)->magic == FAT_CIGAM_64)
	{
		if (argc > 2)
			ft_printf("\n%s:\n", file_name);
		ft_fat_arch(file_content, file_name, ((struct fat_header*)file_content)->magic, file_size);
	}
	else if (!ft_strcmp(file_start, "!<arch>")) // .a
		ft_static_library(file_content, file_name);
	else
		ft_printf("ft_nm: %s %s [%x]\n\n",
			file_name, "The file was not recognized as a valid object file", ((struct fat_header*)file_content)->magic);
	free(file_start);
}

int						main(int argc, char **argv)
{
	char				*file_name;
	int					file_number;
	void				*file_content;
	struct stat			stats;

	file_number = 0;
	if (argc < 2)
	{
		file_name = ft_strdup("a.out");
		argc++;
	}
	while (++file_number < argc)
	{
		file_name = "";
		file_content = NULL;
		if (!(argc == 2 && file_number == 1 && !ft_strcmp(file_name, "a.out")))
			file_name = argv[file_number];
		if (ft_mapping_file(file_name, &file_content, &stats))
			ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
		else
			ft_analyse_file(file_content, file_name, argc, stats.st_size);
		munmap(file_content, stats.st_size);
	}
	return (0);
}
