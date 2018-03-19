/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_element_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:41:53 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 13:42:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		ft_set_element_position(t_symbol_display *ptr,
	t_symbol_display *ptr2, t_symbol_display **list)
{
	if (ft_strcmp(ptr->name, ptr2->name) < 0)
	{
		ptr->next = ptr2;
		ptr->previous = ptr2->previous;
		ptr2->previous = ptr;
		*list = ptr;
		return (1);
	}
	else if (ft_strcmp(ptr->name, ptr2->name) >= 0 && (ptr2->next == NULL
		|| ft_strcmp(ptr->name, (ptr2->next)->name) < 0))
	{
		ptr->next = ptr2->next;
		ptr->previous = ptr2;
		ptr2->next = ptr;
		if (ptr->next)
			(ptr->next)->previous = ptr;
		if (ft_strcmp(ptr->name, ptr2->name) == 0
		&& ptr->value < ptr2->value)
			ft_set_previous_and_next(ptr2, ptr, list);
		return (1);
	}
	return (0);
}
