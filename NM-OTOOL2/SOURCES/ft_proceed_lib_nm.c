/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_lib_nm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:17:20 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/10 15:31:36 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#define DIFF values[0]
#define DISTANCE values[1]

// Meme probleme qu'avec les macho, il manque un 1 dans les adresses des objects

t_symbol_display			*ft_proceed_lib(t_generic_file *gen, int argc)
{
	ft_static_library(gen);
	return (NULL);
}

void				ft_static_library(t_generic_file *gen)
{
	t_static_lib	*lib;
	struct ranlib	*ranlib;
	long int		ranlibs_size;
	t_lib_symbol	*list;

	lib = gen->file_start;
	ranlibs_size = lib->ranlibs_size;
	ranlib = (struct ranlib*)((char*)gen->file_start + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		ft_find_ranlib_symtab(gen, lib, ranlib, &list);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib));
		ranlibs_size -= sizeof(struct ranlib);
	}
	ft_display_static_library_symbols(list, gen);
	ft_free_static_library_symbols(list);
}

void				ft_find_ranlib_symtab(t_generic_file *gen, t_static_lib *lib,
	struct ranlib *ranlib, t_lib_symbol **list)
{
	char			*symbol_name;
	t_static_lib	*obj_header;
	int				values[2];
	char			*file_object_name;
	void			*file_object;

	symbol_name = (char*)(gen->file_start) + sizeof(t_static_lib)
		+ lib->ranlibs_size + ranlib->ran_off;
	obj_header = (t_static_lib*)((char*)(gen->file_start)
		+ (ranlib->ran_un).ran_strx);
	DIFF = (char*)obj_header->end_identifier
		+ ft_strlen(obj_header->end_identifier) - (char*)obj_header;
	DISTANCE = ((DIFF / 8) + 1) * 8;
	DISTANCE = DIFF % 8 > 4 ? DISTANCE + 8 : DISTANCE;
	file_object_name = (char*)(gen->file_start) + sizeof(lib->file_identifier)
		+ (ranlib->ran_un).ran_strx;
	file_object = (char*)obj_header + DISTANCE;
	ft_list_lib_symbols(list, symbol_name, file_object_name, file_object); // Faire continuer gen dans cette fonction
}

void				ft_display_static_library_symbols(t_lib_symbol *list,
	t_generic_file *gen)
{
	t_generic_file		gen2; // Besoin de recuperer la gen originelle.
	unsigned int		start;

	while (list)
	{
		ft_printf("\n%s(%s):\n", gen->file_name, list->file_object_name);
		/***********************************************/
		ft_bzero(&gen2, sizeof(t_generic_file));
		gen2.file_size = 10000000;//Calculer en fonction de la size dans gen
		gen2.file_name = gen->file_name;//file_name;
		gen2.file_start = list->file_object;
		gen2.endian_mach = gen->endian_mach;
		gen2.endian_fat = gen->endian_fat;
		gen2.arch = gen->arch;
		gen2.header = list->file_object;
/*		start = *((unsigned int*)(list->file_object));
		if (start == MH_MAGIC || start == MH_CIGAM)
			gen.arch = 32;
		if (start == MH_CIGAM || start == MH_CIGAM_64)
			gen.endian_mach = LITTLEEND;*/
		/***********************************************/
		ft_find_symtab(&gen2, 1);
		list = list->next;
	}
}
