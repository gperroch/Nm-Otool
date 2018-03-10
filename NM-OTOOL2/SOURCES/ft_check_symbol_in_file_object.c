/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_symbol_in_file_object.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:31:21 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/10 15:31:38 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int						ft_check_symbol_in_file_object(char *symbol_name,
	void *file_object)
{
	t_symbol_display	*list;
	t_symbol_display	*ptr;
	/*******************************/
	t_generic_file		gen; // Besoin de recuperer la gen originelle. Vraiment utile ?
	unsigned int		start;

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.file_size = 10000000;//file_size;
	gen.file_name = "nom_temporaire";//file_name;
	gen.file_start = file_object;
	gen.endian_mach = BIGEND;
	gen.endian_fat = BIGEND;
	gen.arch = 64;
	gen.header = file_object;
	start = *((unsigned int*)file_object);
	if (start == MH_MAGIC || start == MH_CIGAM)
		gen.arch = 32;
	if (start == MH_CIGAM || start == MH_CIGAM_64)
		gen.endian_mach = LITTLEEND;

	list = ft_find_symtab(&gen, 0);
	/****************************/
	/****************************/
	ptr = list;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, symbol_name) && ptr->type >= 65
			&& ptr->type <= 90 && ptr->type != 'U')
		{
//			ft_free_list_symbols(list); // Probleme sur le free
			return (1);
		}
		ptr = ptr->next;
	}
//	ft_free_list_symbols(list); // Probleme sur le free
	return (0);
}
