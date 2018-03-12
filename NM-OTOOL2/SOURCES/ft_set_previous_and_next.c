/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_previous_and_next.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:25:17 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 15:26:05 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_set_previous_and_next(t_symbol_display *ptr,
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
