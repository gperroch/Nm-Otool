/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 12:06:51 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/31 14:56:18 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void					ft_analyse_file(void *file_content, char *file_name)
{
	struct mach_header_64	*header;
	char					*file_start;

	header = file_content;
	file_start = ft_strncpy(ft_strnew(7), file_content, 7);
	if (header->magic == 0xfeedfacf)
	{
		ft_printf("%s:\nContents of (__TEXT,__text) section\n", file_name);
		ft_find_texttext_section(header);
	}
	else if (!ft_strcmp(file_start, "!<arch>"))
	{
		ft_printf("Archive : %s\n", file_name);
		ft_find_texttext_static_library(file_content, file_name);
	}
	else
		ft_printf("ft_otool: '%s': %s\n",
			file_name, "The file was not recognized as a valid object file");
	free(file_start);
}

int							main(int argc, char **argv)
{
	void					*file_content;
	struct stat				stats;
	int						file_number;
	char					*file_name;
	int						mapping_result;

	if (argc < 2)
	{
		ft_printf("error: ft_otool: at least one file must be specified\n");
		return (-1);
	}
	file_number = 1;
	while (file_number < argc)
	{
		file_name = argv[file_number];
		if ((mapping_result = ft_mapping_file(file_name, &file_content, &stats)) > 0)
		{
			ft_analyse_file(file_content, file_name);
			munmap(file_content, stats.st_size);
		}
		else if (mapping_result == 0)
			ft_printf("ft_otool: %s: %s\n", file_name, "Permission denied.");
		else if (mapping_result == -1)
			ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
		else
			ft_printf("ft_otool: '%s': %s\n",
				file_name, "The file was not recognized as a valid object file"); // A mutualiser avec le message de ft_analyse
		file_number++;
	}
	return (0);
}
