/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:53:48 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/22 16:54:50 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_fat_arch(t_generic_file *gen)
{
	uint32_t			i;

	i = -1;
	gen->nfat_arch = gen->fat_header->nfat_arch;
	if (gen->endian_fat == LITTLEEND)
		gen->nfat_arch = ft_swap_endian_32bit(gen->fat_header->nfat_arch);
	while (++i < gen->nfat_arch)
	{
		if (ft_find_arch64(gen, i))
		{
			ft_iterate_fat_arch(gen, i, 1);
			return ;
		}
	}
	i = -1;
	while (++i < gen->nfat_arch)
		ft_iterate_fat_arch(gen, i, 0);
}
