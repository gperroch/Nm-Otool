/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_macho_nm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:14:24 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/21 14:42:19 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_proceed_macho(t_generic_file *gen, int argc)
{
	t_symbol_display	*list;

	if (argc > 2)
		ft_printf("\n%s:\n", gen->file_name);
	gen->header = (t_mach_header_64*)gen->file_start;
	list = ft_find_symtab(gen, 1);
	return (list);
}
