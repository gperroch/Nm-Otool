/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:55:15 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 13:42:08 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_insert_element(t_symbol_display **list,
	t_symbol_display *ptr)
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
		if (ft_set_element_position(ptr, ptr2, list))
			return ;
		ptr2 = ptr2->next;
	}
}
