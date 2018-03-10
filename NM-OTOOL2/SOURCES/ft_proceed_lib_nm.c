/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_lib_nm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:17:20 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/10 14:18:49 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#define DIFF values[0]
#define DISTANCE values[1]


t_symbol_display			*ft_proceed_lib(t_generic_file *gen, int argc)
{
//	ft_printf("Traitement lib nm.\n");
	ft_static_library(gen);
	return (NULL);
}

void				ft_free_static_library_symbols(t_lib_symbol *list)
{
	void			*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp)
			free(tmp);
	}
}

void				ft_static_library(t_generic_file *gen)
{
	// Faire venir ici une gen complete et la rediriger vers ft_find_ranlib_symtab() et ft_display_static_library_symbols()
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
//		printf("ICI\n");
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
		//ft_find_symtab(list->file_object, 1);
		ft_find_symtab(&gen2, 1);
		list = list->next;
	}
}

void					ft_list_lib_symbols(t_lib_symbol **list,
	char *symbol_name, char *file_object_name, void *file_object)
{
	t_lib_symbol		*new_symbol;
	t_lib_symbol		*ptr;

	ptr = *list;
	new_symbol = (t_lib_symbol*)malloc(sizeof(t_lib_symbol));
	ft_bzero(new_symbol, sizeof(t_lib_symbol));
	if (ft_check_symbol_in_file_object(symbol_name, file_object))
		new_symbol->symbol_in_file_object = 1;
	if (!*list)
		*list = new_symbol;
	else
	{
		if (ft_add_symbol_to_list(ptr, new_symbol, file_object_name))
			return ;
	}
	new_symbol->symbol_name = symbol_name;
	new_symbol->file_object_name = file_object_name;
	new_symbol->file_object = file_object;
}

int						ft_add_symbol_to_list(t_lib_symbol *ptr,
	t_lib_symbol *new_symbol, char *file_object_name)
{
	if (!ft_strcmp(ptr->file_object_name, file_object_name)
		&& ptr->symbol_in_file_object)
	{
		free(new_symbol);
		return (-1);
	}
	while (ptr->next)
	{
		ptr = ptr->next;
		if (!ft_strcmp(ptr->file_object_name, file_object_name)
			&& ptr->symbol_in_file_object)
		{
			free(new_symbol);
			return (-1);
		}
	}
	ptr->next = new_symbol;
	new_symbol->previous = ptr;
	ptr = ptr->next;
	return (0);
}

int						ft_check_symbol_in_file_object(char *symbol_name,
	void *file_object)
{
	t_symbol_display	*list;
	t_symbol_display	*ptr;
	/*******************************/
	t_generic_file		gen; // Besoin de recuperer la gen originelle.
	unsigned int		start;

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.file_size = 10000000;//file_size;
	gen.file_name = "nom_temporaire";//file_name;
	gen.file_start = file_object;
	gen.endian_mach = BIGEND;
	gen.endian_fat = BIGEND;
	gen.arch = 64;
	gen.header = file_object;
	start = *((unsigned int*)file_object);
	if (start == MH_MAGIC || start == MH_CIGAM)
		gen.arch = 32;
	if (start == MH_CIGAM || start == MH_CIGAM_64)
		gen.endian_mach = LITTLEEND;

	//list = ft_find_symtab(file_object, 0);
	list = ft_find_symtab(&gen, 0);
	//list = ft_analyse_file(file_object, 3, "nom_temporaire", 1000000000); // Recuperer la taille et le nom ! Probleme avec l'affichage inutile ici.
	/****************************/
	/****************************/
	ptr = list;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, symbol_name) && ptr->type >= 65
			&& ptr->type <= 90 && ptr->type != 'U')
		{
//			ft_free_list_symbols(list);
			return (1);
		}
		ptr = ptr->next;
	}
//	ft_free_list_symbols(list);
	return (0);
}
