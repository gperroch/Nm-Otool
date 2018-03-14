/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_symbols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:22:41 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 14:47:48 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						ft_display_symbols(t_symbol_display *list, t_generic_file *gen) // A OPTIMISER AU NIVEAU DES STRINGS D'AFFICHAGE // PROBLEME SUR L'ADDRESS
{
	while (list)
	{
		if (gen->arch == 64)
		{
			if (list->type == 'U' || list->type == 'u')
				ft_printf("%16c %c %s\n", ' ', list->type, list->name);
			else if (!gen->isLib)
				ft_printf("%016lx %c %s\n", list->value + 0x100000000, list->type, list->name); // Bizzare de devoir faire ca
			else
				ft_printf("%016lx %c %s\n", list->value, list->type, list->name); // Bizzare de devoir faire ca
		}
		else if (gen->arch == 32)
		{
			if (list->type == 'U' || list->type == 'u')
				ft_printf("%8c %c %s\n", ' ', list->type, list->name);
			else
				ft_printf("%08x %c %s\n", list->value, list->type, list->name);
		}
		list = list->next;
	}
}
