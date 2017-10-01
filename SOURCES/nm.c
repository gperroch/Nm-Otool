/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 10:56:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/01 15:39:14 by gperroch         ###   ########.fr       */
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
		find_symtab(header, 1);
	else
		is_static_library(file_content, argv[1]);
	munmap(file_content, stats.st_size);
	return (0);
}
