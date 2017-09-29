/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 10:56:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/29 13:22:46 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include "libft.h"
#include "nm.h"

///Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-migrator/sdks/MacOSX.sdk/usr/include/mach-o/
// Recuperation du contenu de l'executable.
// Mapping des donnees recuperees avec les structures adequat.
// Affichage formate de la table des symboles.
// Attention aux symboles venant de shared libraries.

int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats);
void			ft_display_header(struct mach_header_64 *header);
void			ft_display_load_command(struct load_command *load_command, int ncmds);
void			dump_mem(void *ptr, int len, int col, char *name);
char			*load_command_type(uint32_t cmd);
void			find_symtab(struct mach_header_64 *header);
////////////////////////////////
void		test_strtab(char *ptr, int size);
//////////////////////////////////

int							main(int argc, char **argv)
{
	void					*file_content; // Buffer contenant le fichier.
	struct stat				stats;
	struct mach_header_64	*header;
	struct load_command		*load_command;
	struct segment_command	*segment;
	struct section			*section;

	if (argc < 2 || ft_mapping_file(argv[1], &file_content, &stats))
	{
		printf("ERROR in ft_mapping_file().\n");
		return (-1);
	}
	header = file_content;
	load_command = (struct load_command*)((char*)file_content + sizeof(struct mach_header_64));
//	test_strtab(file_content, stats.st_size);
//	ft_display_header(header);
//	ft_display_load_command(load_command, header->ncmds);
	find_symtab(header);
	munmap(file_content, stats.st_size);
	return (0);
}

int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats)
{
	int			fd;

	fd = open(file_name, O_RDONLY);
    if (fstat(fd, stats))
		return (-1);
//	printf("file size (bytes):%lld\n", stats->st_size);
	if ((*file_content = mmap(0, stats->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	close(fd);
	return (0);
}
