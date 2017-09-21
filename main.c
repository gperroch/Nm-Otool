/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:12:13 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/27 17:36:43 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include "libft.h"

//http://mirror.informatimago.com/next/developer.apple.com/documentation/DeveloperTools/Conceptual/MachORuntime/index.html?http://mirror.informatimago.com/next/developer.apple.com/documentation/DeveloperTools/Conceptual/MachORuntime/8rt_file_format/chapter_10_section_1.html
void 		print_data(void *tmp, int size);

int							main(int argc, char **argv)
{
	struct mach_header_64	*header;
	int						fd;
	uint32_t				magic;
	char					*buffer;
	uint32_t				count;
	int						size_header;
	void					*load_commands;
	struct load_command		*load_command_struct;

	// Recuperation du header
	header = (struct mach_header_64*)malloc(sizeof(struct mach_header_64));
	size_header = sizeof(header);
	printf("size_header = %d\n", size_header);
	ft_bzero(header, size_header);
	fd = open(argv[1], O_RDONLY);
	read(fd, header, sizeof(header));
	printf("Magic number: %x\n", header->magic);
	printf("cputype: %x\n", header->cputype);
	printf("cpusubtype: %x\n", header->cpusubtype);
	printf("filetype: %x\n", header->filetype);
	printf("ncmds: %hu\n", header->ncmds);
	printf("sizeofcmds: %d\n", header->sizeofcmds);
	printf("flags: %x\n", header->flags);
	printf("reserved: %x\n", header->reserved);
	
	// Enregistrement des load commands dans un buffer
	load_commands = malloc(header->sizeofcmds + 1);
	ft_bzero(load_commands, header->sizeofcmds + 1);
	read(fd, load_commands, header->sizeofcmds);

	// Parcours des load commands
	load_command_struct = load_commands;
	while (load_command_struct->cmdsize)
	{
		printf("command type: %hu\n", load_command_struct->cmd);
		printf("cmdsize: %hu\n", load_command_struct->cmdsize);
		printf("load_command_struct = %p\n", load_command_struct);
		load_command_struct = load_command_struct + load_command_struct->cmdsize;
	}
	close(fd);
	return 0;
}
