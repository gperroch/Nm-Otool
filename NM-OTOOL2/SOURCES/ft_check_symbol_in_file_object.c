/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_symbol_in_file_object.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:31:21 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 15:17:49 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int						ft_check_symbol_in_file_object(char *symbol_name, void *file_object)
{
	t_symbol_display	*list;
	t_symbol_display	*ptr;
	t_generic_file		*gen; // Besoin de recuperer la gen originelle. Vraiment utile ? Au moins la taille pour eviter les fichiers corrompus
	unsigned int		start;

	gen = ft_init_gen("nom_temporaire", file_object, 10000000);
	gen->header = file_object;
	start = *((unsigned int*)file_object);
	gen->arch = (start == MH_MAGIC || start == MH_CIGAM) ? 32 : gen->arch;
	gen->endian_mach = (start == MH_CIGAM || start == MH_CIGAM_64) ?
		LITTLEEND : gen->endian_mach;
	list = ft_find_symtab(gen, 0); // Passer par ft_analyse_file pour eviter la creation de cette gen ?? Et pour prendre en compte les lib contenant des fat et des lib, pas seulement des macho ???
	ptr = list;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, symbol_name) && ptr->type >= 65
			&& ptr->type <= 90 && ptr->type != 'U')
		{
			ft_free_list_symbols(list);
			return (1);
		}
		ptr = ptr->next;
	}
	ft_free_list_symbols(list);
	return (0);
}
