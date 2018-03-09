/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:00:26 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 14:11:42 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "libft.h"
#include "nm_otool.h"

#define LIB_MASK 0x213c6172
#define LIB_MASK_2 0x72613c21

void			ft_analyse_file(void *file_content, int argc)
{
	void (*proceeding_function)(void *, int);
	if (*((unsigned int*)file_content) == LIB_MASK || *((unsigned int*)file_content) == LIB_MASK_2) // ?????
		proceeding_function = ft_proceed_lib;

	if (*((unsigned int*)file_content) == FAT_MAGIC)
		proceeding_function = ft_proceed_fat_big32;
	if (*((unsigned int*)file_content) == FAT_MAGIC_64)
		proceeding_function = ft_proceed_fat_big64;
	if (*((unsigned int*)file_content) == FAT_CIGAM)
		proceeding_function = ft_proceed_fat_little32;
	if (*((unsigned int*)file_content) == FAT_CIGAM_64)
		proceeding_function = ft_proceed_fat_little64;

	if (*((unsigned int*)file_content) == MH_MAGIC)
		proceeding_function = ft_proceed_macho_big32;
	if (*((unsigned int*)file_content) == MH_MAGIC_64)
		proceeding_function = ft_proceed_macho_big64;
	if (*((unsigned int*)file_content) == MH_CIGAM)
		proceeding_function = ft_proceed_macho_little32;
	if (*((unsigned int*)file_content) == MH_CIGAM_64)
		proceeding_function = ft_proceed_macho_little64;

	(*proceeding_function)(file_content, argc);
}

////// MACH_O NM //////
void	ft_proceed_macho_big32(void *file_content, int argc)
{
	t_generic_file		gen;
	t_symbol_display	*list;

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.header = (t_mach_header_64*)file_content;
	gen.file_size = 666;//file_size;
	gen.file_name = "tmpfile_name";//file_name;

	ft_printf("Traitement macho big 32bit.\n");
	if (argc > 2)
		ft_printf("\n%s:\n", gen.file_name);
	gen.endian_mach = BIGEND;
	gen.arch = 32;
	//list = ft_find_symtab(header, 1); // 64bit
	list = ft_find_symtab(&gen, 1); // GATEWAY
}
void	ft_proceed_macho_big64(void *file_content, int argc)
{
	t_generic_file		gen;
	t_symbol_display	*list;

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.header = (t_mach_header_64*)file_content;
	gen.file_size = 666;//file_size;
	gen.file_name = "tmpfile_name";//file_name;

	ft_printf("Traitement macho big 64bit.\n");
	if (argc > 2)
		ft_printf("\n%s:\n", gen.file_name);
	gen.endian_mach = BIGEND;
	gen.arch = 64;
	//list = ft_find_symtab(header, 1); // 64bit
	list = ft_find_symtab(&gen, 1); // GATEWAY
}
void	ft_proceed_macho_little32(void *file_content, int argc)
{
	t_generic_file		gen;
	t_symbol_display	*list;

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.header = (t_mach_header_64*)file_content;
	gen.file_size = 666;//file_size;
	gen.file_name = "tmpfile_name";//file_name;

	ft_printf("Traitement macho little 32bit.\n");
	if (argc > 2)
		ft_printf("\n%s:\n", gen.file_name);
	gen.endian_mach = LITTLEEND;
	gen.arch = 32;
	//list = ft_find_symtab(header, 1); // 64bit
	list = ft_find_symtab(&gen, 1); // GATEWAY
}
void	ft_proceed_macho_little64(void *file_content, int argc)
{
	t_generic_file		gen;
	t_symbol_display	*list;

	ft_bzero(&gen, sizeof(t_generic_file));
	gen.header = (t_mach_header_64*)file_content;
	gen.file_size = 666;//file_size;
	gen.file_name = "tmpfile_name";//file_name;

	ft_printf("Traitement macho little 64bit.\n");
	if (argc > 2)
		ft_printf("\n%s:\n", gen.file_name);
	gen.endian_mach = LITTLEEND;
	gen.arch = 64;
	//list = ft_find_symtab(header, 1); // 64bit
	list = ft_find_symtab(&gen, 1); // GATEWAY
}






////// MACH_O OTOOL //////
/*
void	ft_proceed_macho_big32(void *file_content, int argc)
{
	ft_printf("Traitement macho big 32bit.\n");
}
void	ft_proceed_macho_big64(void *file_content, int argc)
{
	ft_printf("Traitement macho big 64bit.\n");
}
void	ft_proceed_macho_little32(void *file_content, int argc)
{
	ft_printf("Traitement macho little 32bit.\n");
}
void	ft_proceed_macho_little64(void *file_content, int argc)
{
	ft_printf("Traitement macho little 64bit.\n");
}
*/







void	ft_proceed_lib(void *file_content, int argc)
{
	ft_printf("Traitement lib.\n");
}

void	ft_proceed_fat_big32(void *file_content, int argc)
{
	ft_printf("Traitement fat big 32bit.\n");
}
void	ft_proceed_fat_big64(void *file_content, int argc)
{
	ft_printf("Traitement fat big 64bit.\n");
}
void	ft_proceed_fat_little32(void *file_content, int argc)
{
	ft_printf("Traitement fat little 32bit.\n");
}
void	ft_proceed_fat_little64(void *file_content, int argc)
{
	ft_printf("Traitement fat little 64bit.\n");
}
