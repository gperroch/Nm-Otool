/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_texttext_static_library.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:03:04 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 12:03:16 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_find_texttext_static_library(void *file_content,
	char *argv)
{
	struct ranlib	*ranlib;
	long int		ranlibs_size;
	t_lib_symbol	*list;
	t_lib_symbol	*ptr;

	ranlibs_size = ((t_static_lib*)file_content)->ranlibs_size;
	ranlib = (struct ranlib*)((char*)file_content + sizeof(t_static_lib));
	ranlibs_size -= sizeof(struct ranlib);
	list = NULL;
	while (ranlibs_size)
	{
		ft_find_ranlib_symbols(file_content, ranlib, &list);
		ranlib = (struct ranlib*)((char*)ranlib + sizeof(ranlib));
		ranlibs_size -= sizeof(struct ranlib);
	}
	ptr = list;
	while (ptr)
	{
		ft_printf("%s(%s):\nContents of (__TEXT,__text) section\n",
			argv, ptr->file_object_name);
		ft_find_texttext_section(ptr->file_object, 64); // BESOIN DE l'ARCHITECTURE
		ptr = ptr->next;
	}
	ft_free_static_library_symbols(list);
}
