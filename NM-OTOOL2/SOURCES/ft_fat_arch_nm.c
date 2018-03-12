/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat_arch_nm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:53:48 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:55:16 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					ft_fat_arch(t_generic_file *gen)
{
	uint32_t			i;

	i = -1;
	if (gen->endian_fat != BIGEND && gen->endian_fat != LITTLEEND)
		return ; // Message d'erreur
	gen->nfat_arch = gen->fat_header->nfat_arch;
	if (gen->endian_fat == LITTLEEND)
		gen->nfat_arch = ft_swap_endian_32bit(gen->fat_header->nfat_arch);
	while (++i < gen->nfat_arch)
		ft_iterate_fat_arch(gen, i); // Attention a ne pas toujours iterer sur toutes les arch. Afficher celle(s) requise(s).
}
