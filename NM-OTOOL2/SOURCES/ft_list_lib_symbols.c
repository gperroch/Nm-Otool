/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_lib_symbols.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:27:04 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/10 15:27:20 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_list_lib_symbols(t_lib_symbol **list,
	char *symbol_name, char *file_object_name, void *file_object)
{
	t_lib_symbol		*new_symbol;
	t_lib_symbol		*ptr;

	ptr = *list;
	new_symbol = (t_lib_symbol*)malloc(sizeof(t_lib_symbol));
	ft_bzero(new_symbol, sizeof(t_lib_symbol));
	if (ft_check_symbol_in_file_object(symbol_name, file_object))  // Faire continuer gen dans cette fonction
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
