/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_ranlib_symbols.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:03:49 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 12:04:03 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				*ft_find_ranlib_symbols(void *file_content,
	struct ranlib *ranlib, t_lib_symbol **list)
{
	t_static_lib	*file_object_header_line;
	void			*file_object;
	char			*file_object_name;
	char			*symbol_name;

	symbol_name = (char*)file_content + sizeof(t_static_lib)
		+ ((t_static_lib*)file_content)->ranlibs_size + ranlib->ran_off;
	file_object_header_line = (t_static_lib*)((char*)file_content
		+ (ranlib->ran_un).ran_strx);
	file_object = (char*)file_object_header_line
		+ ft_calculate_distance_file_object(file_object_header_line);
	file_object_name = (char*)file_content
		+ sizeof(((t_static_lib*)file_content)->file_identifier)
		+ (ranlib->ran_un).ran_strx;
	ft_list_lib_symbols(list, symbol_name, file_object_name, file_object);
	return (file_object);
}
