/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatDescriber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:35:17 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/07 10:46:24 by gperroch         ###   ########.fr       */
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

static void				ft_analyse_file(void *file_content, char *file_name, int argc, off_t file_size);

int		main(int argc, char** argv)
{
	char				*file_name;
	int					file_number;
	void				*file_content;
	struct stat			stats;
	int					mapping_result;

	file_name = argv[1];
	if ((mapping_result = ft_mapping_file(file_name, &file_content, &stats)) > 0)
		ft_analyse_file(file_content, file_name, argc, stats.st_size);
	else
		ft_printf("fatDescriber: %s %s\n\n", file_name, "An error occured.");

	munmap(file_content, stats.st_size);
	return (0);
}

static void				ft_analyse_file(void *file_content, char *file_name, int argc, off_t file_size)
{
	ft_printf("OK./n");
/*	char				*file_start;
	t_symbol_display	*list;
	t_generic_file		gen; // GATEWAY

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.header = (t_mach_header_64*)file_content; // GATEWAY
	gen.file_start = NULL;
	gen.file_size = file_size;
	gen.file_name = file_name;

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
		ft_printf("ft_nm: %s %s\n\n",
			file_name, "The file was not recognized as a valid object file");
	free(file_start);*/
}
