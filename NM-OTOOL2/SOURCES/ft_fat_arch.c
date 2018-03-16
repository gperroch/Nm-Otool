/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:53:48 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 12:12:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

// Si identique a l'autre fat_arch, fusionner

void					ft_fat_arch(t_generic_file *gen)
{
	uint32_t			i;
	int					arch_to_display;

	i = -1;
	arch_to_display = -1;
	if (gen->endian_fat != BIGEND && gen->endian_fat != LITTLEEND)
		return ; // Message d'erreur
	gen->nfat_arch = gen->fat_header->nfat_arch;
	if (gen->endian_fat == LITTLEEND)
		gen->nfat_arch = ft_swap_endian_32bit(gen->fat_header->nfat_arch);

	while (++i < gen->nfat_arch)
	{
		if (ft_find_arch64(gen, i))
		{
			arch_to_display = i;
			i = gen->nfat_arch;
		}
	}

	if (arch_to_display > -1)
		ft_iterate_fat_arch(gen, arch_to_display, 1);
	else
	{
		i = -1;
		while (++i < gen->nfat_arch)
			ft_iterate_fat_arch(gen, i, 0); // Attention a ne pas toujours iterer sur toutes les arch. Afficher celle(s) requise(s).
	}
}
