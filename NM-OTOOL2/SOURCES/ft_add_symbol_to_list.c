/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_symbol_to_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:30:19 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/10 15:30:37 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int						ft_add_symbol_to_list(t_lib_symbol *ptr,
	t_lib_symbol *new_symbol, char *file_object_name)
{
	if (!ft_strcmp(ptr->file_object_name, file_object_name)
		&& ptr->symbol_in_file_object)
	{
		free(new_symbol);
		return (-1);
	}
	while (ptr->next)
	{
		ptr = ptr->next;
		if (!ft_strcmp(ptr->file_object_name, file_object_name)
			&& ptr->symbol_in_file_object)
		{
			free(new_symbol);
			return (-1);
		}
	}
	ptr->next = new_symbol;
	new_symbol->previous = ptr;
	ptr = ptr->next;
	return (0);
}
