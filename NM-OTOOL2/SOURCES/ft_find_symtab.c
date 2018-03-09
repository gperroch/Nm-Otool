/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_symtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:57:57 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 14:16:03 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_find_symtab(t_generic_file *gen, char to_display) // GATEWAY
{
	t_symtab_command		*symtab_command;
	void					*symtab;
	void					*strtab;
	t_symbol_display		*list;

	if (gen->file_start == NULL)
		gen->file_start = gen->header;
	ft_locate_symbol_table(gen, &symtab, &strtab, &symtab_command);
	list = ft_create_symbol_list(symtab, strtab, symtab_command, gen);
/*	if (gen->endian_mach == LITTLEEND)
	{
		ft_locate_symbol_table(gen, &symtab, &strtab, &symtab_command); // GATEWAY
		list = ft_create_symbol_list(symtab, strtab, symtab_command, gen); // !!!
	}
	else if (gen->endian_mach == BIGEND) // GERER ca pour d'autre architectures que FAT
	{
		ft_locate_symbol_table(gen, &symtab, &strtab, &symtab_command); // GATEWAY
		list = ft_create_symbol_list_bigendian(symtab, strtab, symtab_command, gen); // !!!
	}	*/
	//list = ft_create_symbol_list(symtab, strtab, symtab_command, gen); // !!! // 64bit originel

	ft_printf("TRI + AFFICHAGE DES SYMBOLES.\n");
/*
	ft_sort_list_symbols(&list);
	if (to_display)
	{
		ft_display_symbols(list, gen);
		ft_free_list_symbols(list);
	}
*/
	return (list);
}
/*
t_symbol_display			*ft_find_symtab(t_mach_header_64 *header, char to_display) // 64bit
{
	t_symtab_command		*symtab_command;
	void					*symtab;
	void					*strtab;
	t_symbol_display		*list;

	ft_locate_symbol_table(header, &symtab, &strtab, &symtab_command); // 64bit
	list = ft_create_symbol_list(symtab, strtab, symtab_command, header);
	ft_sort_list_symbols(&list);
	if (to_display)
	{
		ft_display_symbols(list);
		ft_free_list_symbols(list);
	}
	return (list);
}
*/
