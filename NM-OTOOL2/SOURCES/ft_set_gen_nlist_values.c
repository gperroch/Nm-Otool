/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_gen_nlist_values.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:46:04 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/21 15:38:16 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_set_gen_nlist_values(t_generic_file *gen)
{
	gen->n_type = gen->arch == 32 ?
		(gen->nlist)->n_type : (gen->nlist_64)->n_type;
	gen->n_sect = gen->arch == 32 ?
		(gen->nlist)->n_sect : (gen->nlist_64)->n_sect;
	gen->n_desc = gen->arch == 32 ?
		(gen->nlist)->n_desc : (gen->nlist_64)->n_desc;
	gen->n_value = gen->arch == 32 ?
		(gen->nlist)->n_value : (gen->nlist_64)->n_value;
	gen->n_strx = gen->arch == 32 ?
		(gen->nlist)->n_un.n_strx : (gen->nlist_64)->n_un.n_strx;
	if (gen->endian_mach == LITTLEEND)
	{
		gen->n_value = ft_swap_endian_32bit(gen->n_value);
		gen->n_strx = ft_swap_endian_32bit(gen->n_strx);
	}
/*	ft_printf("(gen->nlist)->n_type = %hhd, (gen->nlist_64)->n_type = %hhd\n", (gen->nlist)->n_type, (gen->nlist_64)->n_type);
	ft_printf("(gen->nlist)->n_sect = %hhd, (gen->nlist_64)->n_sect = %hhd\n", (gen->nlist)->n_sect, (gen->nlist_64)->n_sect);
	ft_printf("(gen->nlist)->n_desc = %hd, (gen->nlist_64)->n_desc = %hd\n", (gen->nlist)->n_desc, (gen->nlist_64)->n_desc);
	ft_printf("(gen->nlist)->n_value = %lx, (gen->nlist_64)->n_value = %lx\n", (gen->nlist)->n_value, (gen->nlist_64)->n_value);
	ft_printf("(gen->nlist)->n_un.n_strx = %d, (gen->nlist_64)->n_un.n_strx = %d\n\n", (gen->nlist)->n_un.n_strx, (gen->nlist_64)->n_un.n_strx);*/
}
