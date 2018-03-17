/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_fat_otool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:16:40 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 17:08:20 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_proceed_fat(t_generic_file *gen, int argc)
{
	gen->fat_header = (struct fat_header*)(gen->file_start);
	gen->otool = 1;
	if (argc > 2)
		ft_printf("\n%s:\n", gen->file_name);
	ft_fat_arch(gen);
	return (NULL);
}
