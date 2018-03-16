/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:23:56 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 14:05:47 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

// Faire le tri a la creation de la liste.

void					ft_sort_list_symbols(t_symbol_display **list)
{
	t_symbol_display	*ptr;
	t_symbol_display	*ptr2;
	char				modified;
/*
	t_symbol_display	*tmp;
	tmp = *list;
	while (tmp)
	{
		ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
*/
	modified = 1;
	while (modified)
	{
		modified = 0;
		ptr = *list;
		while (ptr && ptr->next)
		{
			ptr2 = ptr->next;
			if (ft_strcmp(ptr->name, ptr2->name) > 0)
			{
				//ft_printf("[%s] [%s]\n", ptr->name, ptr2->name); // Tri infini sur /usr/bin/ccmake
				ft_set_previous_and_next(ptr, ptr2, list);
				modified = 1;
			}
			ptr = ptr2;
		}
	}
}
