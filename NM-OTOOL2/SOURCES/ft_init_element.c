/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:19:25 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 15:19:40 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						ft_init_element(t_symbol_display **list,
	t_symbol_display **ptr)
{
	if (!*list)
	{
		*list = (t_symbol_display*)malloc(sizeof(t_symbol_display));
		*ptr = *list;
		(*ptr)->next = NULL;
		(*ptr)->previous = NULL;
	}
	else
	{
		(*ptr)->next = (t_symbol_display*)malloc(sizeof(t_symbol_display));
		(*ptr)->next->previous = *ptr;
		(*ptr) = (*ptr)->next;
		(*ptr)->next = NULL;
	}
}
