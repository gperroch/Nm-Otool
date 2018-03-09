/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:00:26 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 10:57:27 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "libft.h"
void		dump_mem(void *ptr, int len, int col, char *name);
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

void			ft_analyse_file(void *file_content)
{
	if (*((int*)file_content) == LIB_MASK)
		ft_printf("Traitement lib.\n");

	if (*((unsigned int*)file_content) == FAT_MAGIC)
		ft_printf("Traitement fat big 32bit.\n");
	if (*((unsigned int*)file_content) == FAT_MAGIC_64)
		ft_printf("Traitement fat big 64bit.\n");
	if (*((unsigned int*)file_content) == FAT_CIGAM)
		ft_printf("Traitement fat little 32bit.\n");
	if (*((unsigned int*)file_content) == FAT_CIGAM_64)
		ft_printf("Traitement fat little 64bit.\n");

	if (*((unsigned int*)file_content) == MH_MAGIC)
		ft_printf("Traitement macho big 32bit.\n");
	if (*((unsigned int*)file_content) == MH_MAGIC_64)
		ft_printf("Traitement macho big 64bit.\n");
	if (*((unsigned int*)file_content) == MH_CIGAM)
		ft_printf("Traitement macho little 32bit.\n");
	if (*((unsigned int*)file_content) == MH_CIGAM_64)
		ft_printf("Traitement macho little 64bit.\n");
}
