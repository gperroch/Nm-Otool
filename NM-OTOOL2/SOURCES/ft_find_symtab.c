/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_symtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:57:57 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/21 15:36:05 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_find_symtab(t_generic_file *gen,
	char to_display)
{
	t_symtab_command		*symtab_command;
	void					*symtab;
	void					*strtab;
	t_symbol_display		*list;

	ft_locate_symbol_table(gen, &symtab, &strtab, &symtab_command);
	list = ft_create_symbol_list(symtab, strtab, symtab_command, gen);
	if (to_display)
	{
		ft_display_symbols(list, gen);
		ft_free_list_symbols(list);
	}
	return (list);
}
