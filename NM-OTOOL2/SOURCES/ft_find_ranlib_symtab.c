/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_ranlib_symtab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:58:59 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:59:42 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#define DIFF values[0]
#define DISTANCE values[1]

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
