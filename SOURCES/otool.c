/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 12:06:51 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/01 15:00:50 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		main(int argc, char **argv)
{
	void					*file_content; // Buffer contenant le fichier.
	struct stat				stats;
	struct mach_header_64	*header;

	if (argc < 2 || ft_mapping_file(argv[1], &file_content, &stats))
	{
		printf("ERROR in ft_mapping_file().\n");
		return (-1);
	}
	header = file_content; // Parsing a faire a ce niveau.
	if (header->magic == 0xfeedfacf)
	{
		printf("%s:\nContents of (__TEXT,__text) section\n", argv[1]);
		find_texttext_section(header);
	}
	else
	{
		printf("Archive : %s\n", argv[1]);
		find_texttext_static_library(file_content, argv[1]);
	}
	munmap(file_content, stats.st_size);
	return (0);
}
