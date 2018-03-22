/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_symbol_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:23:58 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/22 16:39:45 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab,
	t_symtab_command *symtab_command, t_generic_file *gen)
{
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	int						symbol_counter;
	int						symbol_max;

	gen->nlist = symtab;
	gen->nlist_64 = symtab;
	symbol_counter = -1;
	symbol_max = (gen->endian_mach == LITTLEEND) ?
		ft_swap_endian_32bit(symtab_command->nsyms) : symtab_command->nsyms;
	list = NULL;
	while (++symbol_counter < symbol_max)
	{
		if (!ft_bounds_security(gen, gen->nlist)) // Necessite gen.file_size et gen.file_start pour fonctionner
			return (NULL);
		ft_set_gen_nlist_values(gen);
		if (!(gen->n_type & N_STAB))
		{
			ptr = ft_create_element(gen, strtab);
			ft_insert_element(&list, ptr);
		}
		gen->nlist = (void*)((char*)gen->nlist + sizeof(struct nlist));
		gen->nlist_64 = (void*)((char*)gen->nlist_64 + sizeof(struct nlist_64));
	}
	return (list);
}
