/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:55:15 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 11:06:45 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_insert_element(t_symbol_display **list, t_symbol_display *ptr)
{
	t_symbol_display	*ptr2;

	if (!*list)
	{
		*list = ptr;
		return ;
	}

	ptr2 = *list;
	while (ptr2)
	{
		if (ft_strcmp(ptr->name, ptr2->name) < 0)
		{
			ptr->next = ptr2;
			ptr->previous = ptr2->previous;
			ptr2->previous = ptr;
			*list = ptr;
			return ;
		}
		else if (ft_strcmp(ptr->name, ptr2->name) >= 0 && (ptr2->next == NULL || ft_strcmp(ptr->name, (ptr2->next)->name) < 0))
		{
			ptr->next = ptr2->next;
			ptr->previous = ptr2;
			ptr2->next = ptr;
			if (ptr->next)
				(ptr->next)->previous = ptr;
			return ;
		}
/*		else if (ft_strcmp(ptr->name, ptr2->name) == 0) //comparaison des adresses
		{

		}
*/		ptr2 = ptr2->next;
	}
	ft_printf("OUT FOR [%s]\n", ptr->name);
}
