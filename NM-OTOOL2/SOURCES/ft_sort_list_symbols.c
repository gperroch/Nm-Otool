/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:23:56 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 15:24:10 by gperroch         ###   ########.fr       */
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
