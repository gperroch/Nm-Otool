/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 10:56:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/21 11:30:42 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include "libft.h"

// Recuperation du contenu de l'executable.
// Mapping des donnees recuperees avec les structures adequat.
// Affichage formate de la table des symboles.
// Attention aux symboles venant de shared libraries.

int				ft_mapping_file(char *file_name, void **file_content);

int							main(int argc, char **argv)
{
	void					*file_content; // Buffer contenant le fichier.
	struct mach_header		*header;
	struct load_command		*load_command;
	struct segment_command	*segment;
	struct section			*section;

	if (argc < 2 || ft_mapping_file(argv[1], &file_content))
	{
		printf("ERROR in ft_mapping_file().\n");
		return (-1);
	}
	header = file_content;
	free(file_content);
	return (0);
}

int				ft_mapping_file(char *file_name, void **file_content)
{
	int			fd;
	struct stat	*buf;

	fd = open(file_name, O_RDONLY);
	buf = (struct stat*)malloc(sizeof(buf));
	printf("fd:%d\n", fd);
    if (fstat(fd, buf))
		return (-1);
	printf("file size (bytes):%lld\n", buf->st_size);
	(*file_content) = malloc(sizeof(char) * (buf->st_size + 1));
	ft_bzero(*file_content, buf->st_size + 1);
	read(fd, *file_content, buf->st_size);
	close(fd);
	return (0);
}
