/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:00:26 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 11:23:57 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "libft.h"
void		dump_mem(void *ptr, int len, int col, char *name);
void	ft_proceed_lib(void *file_content);
void	ft_proceed_fat_big32(void *file_content);
void	ft_proceed_fat_big64(void *file_content);
void	ft_proceed_fat_little32(void *file_content);
void	ft_proceed_fat_little64(void *file_content);
void	ft_proceed_macho_big32(void *file_content);
void	ft_proceed_macho_big64(void *file_content);
void	ft_proceed_macho_little32(void *file_content);
void	ft_proceed_macho_little64(void *file_content);
// Liste des masks :
// FAT_MAGIC
// FAT_MAGIC_64
// FAT_CIGAM
// FAT_CIGAM_64
// MH_MAGIC
// MH_MAGIC_64
// MH_CIGAM
// MH_CIGAM_64
// LIB_MASK 0x213c6172

#define LIB_MASK 0x213c6172
#define LIB_MASK_2 0x72613c21

void			ft_analyse_file(void *file_content)
{
	void (*proceeding_function)(void *);
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

	(*proceeding_function)(file_content);
}

void	ft_proceed_lib(void *file_content)
{
	ft_printf("Traitement lib.\n");
}

void	ft_proceed_fat_big32(void *file_content)
{
	ft_printf("Traitement fat big 32bit.\n");
}
void	ft_proceed_fat_big64(void *file_content)
{
	ft_printf("Traitement fat big 64bit.\n");
}
void	ft_proceed_fat_little32(void *file_content)
{
	ft_printf("Traitement fat little 32bit.\n");
}
void	ft_proceed_fat_little64(void *file_content)
{
	ft_printf("Traitement fat little 64bit.\n");
}

void	ft_proceed_macho_big32(void *file_content)
{
	ft_printf("Traitement macho big 32bit.\n");
}
void	ft_proceed_macho_big64(void *file_content)
{
	ft_printf("Traitement macho big 64bit.\n");
}
void	ft_proceed_macho_little32(void *file_content)
{
	ft_printf("Traitement macho little 32bit.\n");
}
void	ft_proceed_macho_little64(void *file_content)
{
	ft_printf("Traitement macho little 64bit.\n");
}
