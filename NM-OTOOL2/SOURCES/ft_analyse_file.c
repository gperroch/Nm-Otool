/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:00:26 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 17:37:40 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_analyse_file(void *file_content, int argc, char *file_name, off_t file_size)
{
	unsigned int	start;
	t_generic_file	gen;
	void 			(*proceeding_function)(t_generic_file*, int);

	proceeding_function = NULL;
	ft_bzero(&gen, sizeof(t_generic_file));
	gen.file_size = file_size;
	gen.file_name = file_name;
	gen.file_start = file_content;
	gen.endian_mach = BIGEND;
	gen.endian_fat = BIGEND;
	gen.arch = 64;

	start = *((unsigned int*)file_content);


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
		gen.endian_fat = LITTLEEND;

	if (proceeding_function)
		(*proceeding_function)(&gen, argc);
	else
		ft_errors(INVALID_FILE, 0, file_name);
}

////// MACH_O NM //////
void	ft_proceed_macho(t_generic_file *gen, int argc)
{
	t_symbol_display	*list;

	if (argc > 2)
		ft_printf("\n%s:\n", gen->file_name);
	gen->header = (t_mach_header_64*)gen->file_start;
	list = ft_find_symtab(gen, 1); // GATEWAY
}

////// FAT NM //////
void	ft_proceed_fat(t_generic_file *gen, int argc)
{
	gen->fat_header = (struct fat_header*)(gen->file_start);
	if (argc > 2)
		ft_printf("\n%s:\n", gen->file_name);
	ft_fat_arch(gen); // Changer les params et gen
}



////// FAT OTOOL //////
/*
void	ft_proceed_fat(t_generic_file *gen, int argc)
{
	ft_printf("Traitement fat big 32bit.\n");
}
*/
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
