/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_symbols.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:11:17 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/02 16:29:44 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_sort_list_symbols(t_symbol_display **list)
{
	t_symbol_display	*ptr;
	t_symbol_display	*ptr2;
	char				modified;

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
				ft_set_previous_and_next(ptr, ptr2, list);
				modified = 1;
			}
			ptr = ptr2;
		}
	}
}

void				ft_set_previous_and_next(t_symbol_display *ptr,
	t_symbol_display *ptr2, t_symbol_display **list)
{
	if (ptr->previous)
		(ptr->previous)->next = ptr2;
	else
		*list = ptr2;
	if (ptr2->next)
		(ptr2->next)->previous = ptr;
	ptr->next = ptr2->next;
	ptr2->previous = ptr->previous;
	ptr->previous = ptr2;
	ptr2->next = ptr;
}
