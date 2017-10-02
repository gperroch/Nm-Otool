/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 10:56:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/02 18:31:21 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

///Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-migrator/sdks/MacOSX.sdk/usr/include/mach-o/
// Recuperation du contenu de l'executable.
// Mapping des donnees recuperees avec les structures adequat.
// Affichage formate de la table des symboles.
// Attention aux symboles venant de shared libraries.

// PARSING ET CAS D'ERREURS (+return adequat) DANS TOUTES LES FONCTIONS
// VERIFIER LES LEAKS
// METTRE TOUTES LES FONCTIONS EN FT_...
// GERER LES DIFFERENTS TYPES DE HEADER (pas seulement mach_header_64)
// GERER LES MULTIPLES FICHIERS EN PARAMETRES
// AFFICHER AVEC AUTRE CHOSE QUE PRINTF

// Attention aux arguments de la forme libx.a(x.o)

int							main(int argc, char **argv)
{
	char					*file_name;
	int						file_number;
	void					*file_content; // Buffer contenant le fichier.
	struct stat				stats;

	file_name = "";
	file_number = 0;
	if (argc < 2)
	{
		file_name = ft_strdup("a.out");
		argc++;
	}
	while (++file_number < argc)
	{
		if (!(argc == 2 && file_number == 1 && !ft_strcmp(file_name, "a.out")))
			file_name = argv[file_number];
		if (ft_mapping_file(file_name, &file_content, &stats))
			ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
		else
			ft_analyse_file(file_content, file_name);
		munmap(file_content, stats.st_size);
	}
	return (0);
}

void					ft_analyse_file(void *file_content, char *file_name)
{
	t_mach_header_64	*header;
	char					*file_start;

	header = file_content; // Parsing a faire a ce niveau.
	file_start = ft_strncpy(ft_strnew(7), file_content, 7);
	if (header->magic == 0xfeedfacf)
		ft_find_symtab(header, 1);
	else if (!ft_strcmp(file_start, "!<arch>"))
		ft_static_library(file_content, file_name);
	else
		ft_printf("ft_nm: %s The file was not recognized as a valid object file\n", file_name);
	free(file_start);
}
