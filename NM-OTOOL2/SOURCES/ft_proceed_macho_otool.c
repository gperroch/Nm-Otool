/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_macho_otool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:16:02 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 12:04:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_proceed_macho(t_generic_file *gen, int argc)
{
	(void)argc; // ??
	ft_printf("%s:\nContents of (__TEXT,__text) section\n", gen->file_name);
	gen->header = gen->file_start;
	ft_find_texttext_section(gen->header, gen->arch);
	return (NULL);
}