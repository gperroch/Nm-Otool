/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_texttext_static_library.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:03:04 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 14:00:23 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_find_texttext_static_library(t_generic_file *gen)
{
	t_lib_symbol	*list;
	t_lib_symbol	*ptr;
	t_generic_file	*gen2;

	list = NULL;
	ft_iter_ranlibs(gen, &list);
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
