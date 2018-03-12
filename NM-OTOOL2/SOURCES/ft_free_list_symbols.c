/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:19:01 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 14:19:15 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_free_list_symbols(t_symbol_display *list)
{
	t_symbol_display	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp)
			free(tmp);
	}
}
