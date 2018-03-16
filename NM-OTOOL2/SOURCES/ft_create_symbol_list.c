/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_symbol_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:23:58 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 11:35:18 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab, t_symtab_command *symtab_command, t_generic_file *gen)
{
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	int				symbol_counter;
	int				symbol_max;

	gen->nlist = symtab;
	gen->nlist_64 = symtab;

	symbol_counter = 0;
	if (gen->endian_mach == LITTLEEND)
		symbol_max = ft_swap_endian_32bit(symtab_command->nsyms);
	else
		symbol_max = symtab_command->nsyms;
	list = NULL;
	while (symbol_counter < symbol_max)
	{
		if ((gen->arch == 32 && !ft_bounds_security(gen, gen->nlist)) || (gen->arch == 64 && !ft_bounds_security(gen, gen->nlist_64))) // Necessite gen.file_size et gen.file_start pour fonctionner
			return (NULL);
//		dump_mem()
		gen->n_type = gen->arch == 32 ? (gen->nlist)->n_type : (gen->nlist_64)->n_type;
		gen->n_sect = gen->arch == 32 ? (gen->nlist)->n_sect : (gen->nlist_64)->n_sect;
		gen->n_desc = gen->arch == 32 ? (gen->nlist)->n_desc : (gen->nlist_64)->n_desc;
		gen->n_value = gen->arch == 32 ? (gen->nlist)->n_value : (gen->nlist_64)->n_value;
		gen->n_strx = gen->arch == 32 ? (gen->nlist)->n_un.n_strx : (gen->nlist_64)->n_un.n_strx;
		if (gen->endian_mach == LITTLEEND)
		{
			gen->n_value = ft_swap_endian_32bit(gen->n_value);
			gen->n_strx = ft_swap_endian_32bit(gen->n_strx);
		}
		if (!(gen->n_type & N_STAB))
		{
			// Faire le tri ici. Placer le nouvel element au bon endroit.
//			ft_init_element(&list, &ptr); // A enlever de la compilation et du projet
//			ft_set_element(&ptr, gen, strtab); // A enlever de la compilation et du projet
			ptr = ft_create_element(gen, strtab);
			ft_insert_element(&list, ptr);
		}
		gen->nlist = (struct nlist*)((char*)gen->nlist + sizeof(struct nlist));
		gen->nlist_64 = (struct nlist_64*)((char*)gen->nlist_64 + sizeof(struct nlist_64));
		symbol_counter++;
	}
	return (list);
}
