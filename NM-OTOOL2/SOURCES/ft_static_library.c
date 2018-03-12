/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_library.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:58:09 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:58:29 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

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
