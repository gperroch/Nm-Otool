/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:00:26 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 16:09:07 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		ft_analyse_file(void *file_content, int argc,
	char *file_name, off_t file_size)
{
	unsigned int		start;
	t_generic_file		*gen;
	t_symbol_display	*(*proceeding_function)(t_generic_file*, int);

	proceeding_function = NULL;
	gen = ft_init_gen(file_name, file_content, file_size);
	start = *((unsigned int*)file_content);
	if (start == LIB_MASK || start == LIB_MASK_2) // ?????
		proceeding_function = ft_proceed_lib;
	if (start == MH_MAGIC || start == MH_CIGAM
		|| start == MH_MAGIC_64 || start == MH_CIGAM_64)
		proceeding_function = ft_proceed_macho;
	if (start == MH_MAGIC || start == MH_CIGAM
		|| start == FAT_MAGIC || start == FAT_CIGAM)
		gen->arch = 32;
	if (start == MH_CIGAM || start == MH_CIGAM_64)
		gen->endian_mach = LITTLEEND;
	if (start == FAT_MAGIC || start == FAT_CIGAM
		|| start == FAT_MAGIC_64 || start == FAT_CIGAM_64)
		proceeding_function = ft_proceed_fat;
	if (start == FAT_CIGAM || start == FAT_CIGAM_64)
		gen->endian_fat = LITTLEEND;
	if (proceeding_function)
		(*proceeding_function)(gen, argc);
	else
		ft_errors(INVALID_FILE, file_name);
}
