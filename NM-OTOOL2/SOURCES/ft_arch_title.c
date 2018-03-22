/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arch_title.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:31:56 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/22 18:13:35 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void			ft_arch_title(t_generic_file *gen, int onlyone,	void *fat_arch)
{
	char				*cputype;

	if (gen->endian_fat == BIGEND)
		cputype = ft_get_arch_type(((struct fat_arch_64*)fat_arch)->cputype);
	else if (gen->endian_fat == LITTLEEND)
		cputype = ft_get_arch_type(
			ft_swap_endian_32bit(((struct fat_arch_64*)fat_arch)->cputype));
	else
		cputype = ft_strdup("undefined");
	if (!onlyone && gen->nfat_arch != 1 && !(gen->otool))
		ft_printf("\n%s (for architecture %s):\n", gen->file_name, cputype);
	else if (!onlyone && gen->nfat_arch != 1 && gen->otool)
		ft_printf("%s (architecture %s):\n", gen->file_name, cputype);
	//else if (!onlyone && gen->nfat_arch == 1 && !(gen->otool))
	else if (gen->nfat_arch == 1 && !(gen->otool))
		ft_printf("%s:\n", gen->file_name);
	if (!ft_strcmp(cputype, "ppc"))
		g_isppc = 1;
	else
		g_isppc = 0;
	free(cputype);
}
