/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_macho_otool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:16:02 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 17:15:15 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_proceed_macho(t_generic_file *gen, int argc)
{
	(void)argc; // ??
	ft_printf("%s:\nContents of (__TEXT,__text) section\n", gen->file_name);
	gen->header = gen->file_start;
	gen->otool = 1;
	ft_find_texttext_section(gen);
	return (NULL);
}
