/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:00:26 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 16:30:35 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void			ft_analyse_file(void *file_content, int argc, char *file_name, off_t file_size)
{
	unsigned int	start;
	t_generic_file	gen;

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.header = (t_mach_header_64*)file_content;
	gen.file_size = file_size;
	gen.file_name = file_name;
	gen.endian_mach = BIGEND;
	gen.arch = 64;

	start = *((unsigned int*)file_content);
	void (*proceeding_function)(t_generic_file*, int);

	if (start == LIB_MASK || *((unsigned int*)file_content) == LIB_MASK_2) // ?????
		proceeding_function = ft_proceed_lib;

	if (start == MH_MAGIC || start == MH_CIGAM || start == MH_MAGIC_64 || start == MH_CIGAM_64)
		proceeding_function = ft_proceed_macho;
	if (start == MH_MAGIC || start == MH_CIGAM)
		gen.arch = 32;
	if (start == MH_CIGAM || start == MH_CIGAM_64)
		gen.endian_mach = LITTLEEND;

	if (start == FAT_MAGIC || start == FAT_CIGAM || start == FAT_MAGIC_64 || start == FAT_CIGAM_64)
		proceeding_function = ft_proceed_fat;
	if (start == FAT_MAGIC || start == FAT_CIGAM)
		gen.arch = 32;
	if (start == FAT_CIGAM || start == FAT_CIGAM_64)
		gen.endian_mach = LITTLEEND;

	(*proceeding_function)(&gen, argc);
}

////// MACH_O NM //////
void	ft_proceed_macho(t_generic_file *gen, int argc)
{
	t_symbol_display	*list;

	if (argc > 2)
		ft_printf("\n%s:\n", gen->file_name);
	list = ft_find_symtab(gen, 1); // GATEWAY
}

////// MACH_O OTOOL //////
/*
void	ft_proceed_macho(t_generic_file *gen, int argc)
{
}
*/







void	ft_proceed_lib(t_generic_file *gen, int argc)
{
	ft_printf("Traitement lib.\n");
}
////// FAT NM //////
void	ft_proceed_fat(t_generic_file *gen, int argc)
{
	ft_printf("Traitement fat big 32bit.\n");
}

////// FAT OTOOL //////
/*
void	ft_proceed_fat(t_generic_file *gen, int argc)
{
	ft_printf("Traitement fat big 32bit.\n");
}
*/
