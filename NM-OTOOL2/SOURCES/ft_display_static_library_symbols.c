/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_static_library_symbols.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:03:55 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 18:04:19 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_display_static_library_symbols(t_lib_symbol *list,
	t_generic_file *gen)
{
	t_generic_file		gen2; // Besoin de recuperer la gen originelle.
	//unsigned int		start;

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
