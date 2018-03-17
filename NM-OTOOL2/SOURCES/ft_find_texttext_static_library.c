/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_texttext_static_library.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:03:04 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 16:52:33 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_find_texttext_static_library(t_generic_file *gen)
{
	struct ranlib	*ranlib;
	long int		ranlibs_size;
	t_lib_symbol	*list;
	t_lib_symbol	*ptr;
	t_generic_file	*gen2;

	ranlibs_size = ((t_static_lib*)(gen->file_start))->ranlibs_size;
	ranlib = (struct ranlib*)((char*)(gen->file_start) + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		ft_find_ranlib_symbols((gen->file_start), ranlib, &list);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib));
		ranlibs_size -= sizeof(struct ranlib);
	}
	ptr = list;
	while (ptr)
	{
		ft_printf("%s(%s):\nContents of (__TEXT,__text) section\n",
			gen->file_name, ptr->file_object_name);
		gen2 = ft_init_gen(gen->file_name, ptr->file_object, gen->file_size); // size a changer (incorrecte ici)
		gen2->endian_mach = gen->endian_mach;
		gen2->arch = gen->arch;
		gen2->header = gen2->file_start;
		ft_find_texttext_section(gen2);
		ptr = ptr->next;
	}
	ft_free_static_library_symbols(list);
}
