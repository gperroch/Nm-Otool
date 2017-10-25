/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 10:56:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/25 10:57:52 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

// 32-bit
// .dylib
// Architectures FAT
// Securite segfault sur les fichiers corrompus
// Bonus -p -u -U -j -r

static void				ft_analyse_file(void *file_content, char *file_name,
	int argc)
{
	t_mach_header_64	*header;
	char				*file_start;
	t_symbol_display	*list;

	header = file_content;
	file_start = ft_strncpy(ft_strnew(7), file_content, 7);
	if (header->magic == 0xfeedfacf) // mach-o 64-bits x86
	{
		if (argc > 2)
			ft_printf("\n%s:\n", file_name);
		list = ft_find_symtab(header, 1);
	}
	else if (!ft_strcmp(file_start, "!<arch>")) // .a
		ft_static_library(file_content, file_name);
	else
		ft_printf("ft_nm: %s %s\n\n",
			file_name, "The file was not recognized as a valid object file");
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
			ft_analyse_file(file_content, file_name, argc);
		munmap(file_content, stats.st_size);
	}
	return (0);
}
