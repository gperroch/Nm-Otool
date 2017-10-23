/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_list_symbol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 18:26:54 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/19 18:51:56 by gperroch         ###   ########.fr       */
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
	if (ft_check_symbol_in_file_object(symbol_name, file_object))
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

int						ft_check_symbol_in_file_object(char *symbol_name,
	void *file_object)
{
	t_symbol_display	*list;
	t_symbol_display	*ptr;

	list = ft_find_symtab(file_object, 0);
	ptr = list;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, symbol_name) && ptr->type >= 65
			&& ptr->type <= 90 && ptr->type != 'U')
		{
			ft_free_list_symbols(list);
			return (1);
		}
		ptr = ptr->next;
	}
	ft_free_list_symbols(list);
	return (0);
}
