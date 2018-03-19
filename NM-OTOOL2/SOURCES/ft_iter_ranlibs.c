/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_ranlibs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:00:09 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 14:00:27 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_iter_ranlibs(t_generic_file *gen, t_lib_symbol **list)
{
	struct ranlib	*ranlib;
	long int		ranlibs_size;

	ranlibs_size = ((t_static_lib*)(gen->file_start))->ranlibs_size;
	ranlib = (struct ranlib*)((char*)(gen->file_start) + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		ft_find_ranlib_symbols((gen->file_start), ranlib, list);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib));
		ranlibs_size -= sizeof(struct ranlib);
	}
}
