/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_library.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:28:40 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/02 18:28:44 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_static_library(void *file_content, char *file_name)
{
	t_static_lib	*lib;
	struct ranlib	*ranlib;
	long int		ranlibs_size;
	t_lib_symbol	*list;

	lib = file_content;
	ranlibs_size = lib->ranlibs_size;
	ranlib = (struct ranlib*)((char*)file_content + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		ft_find_ranlib_symtab(file_content, lib, ranlib, &list);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib)); // VERIFIER LA PRESENCE DE ran_name AVEC UN IFDEF __LP64__
		ranlibs_size -= sizeof(struct ranlib);
	}
	ft_display_static_library_symbols(list, file_name);
}

void				ft_find_ranlib_symtab(void *file_content, t_static_lib *lib,
	 struct ranlib *ranlib, t_lib_symbol **list)
{
	char			*symbol_name;
	t_static_lib	*obj_header;
	int				diff;
	int				distance;
	char			*file_object_name;
	void			*file_object;

	symbol_name = (char*)file_content + sizeof(t_static_lib)
		+ lib->ranlibs_size + ranlib->ran_off;
	obj_header = (t_static_lib*)((char*)file_content
		+ (ranlib->ran_un).ran_strx);
	diff = (char*)obj_header->end_identifier
		+ ft_strlen(obj_header->end_identifier) - (char*)obj_header;
	distance = ((diff / 8) + 1) * 8;
	distance = diff % 8 > 4 ? distance + 8 : distance;
	file_object_name = (char*)file_content + sizeof(lib->file_identifier)
		+ (ranlib->ran_un).ran_strx;
	file_object = (char*)obj_header + distance;
	ft_list_lib_symbols(list, symbol_name, file_object_name, file_object);
}

void				ft_display_static_library_symbols(t_lib_symbol *list,
	char *file_name)
{
	while (list)
	{
		printf("\n%s(%s):\n", file_name, list->file_object_name);
		ft_find_symtab(list->file_object, 1);
		list = list->next;
	}
}
