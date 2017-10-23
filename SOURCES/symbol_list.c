/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:39:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/19 18:52:09 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab,
	t_symtab_command *symtab_command, t_mach_header_64 *header)
{
	struct nlist_64			*nlist;
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	uint32_t				symbol_counter;

	symbol_counter = 0;
	nlist = symtab;
	list = NULL;
	while (symbol_counter < symtab_command->nsyms)
	{
		if (!(nlist->n_type & N_STAB))
		{
			ft_init_element(&list, &ptr);
			ft_set_element(&ptr, nlist, header, strtab);
		}
		nlist = (struct nlist_64*)((char*)nlist + sizeof(struct nlist_64));
		symbol_counter++;
	}

	return (list);
}

void						ft_set_element(t_symbol_display **ptr,
	struct nlist_64 *nlist, t_mach_header_64 *header, void *strtab)
{
	(*ptr)->value = nlist->n_value;
	(*ptr)->name = &((char*)strtab)[(nlist->n_un).n_strx];
	(*ptr)->type = 'U';
	(*ptr)->type = nlist->n_type & N_STAB ? '-' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_UNDF ? 'U' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_ABS ? 'A' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_INDR ? 'I' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_PBUD ? 'U' : (*ptr)->type;
	(*ptr)->type = (nlist->n_type & N_TYPE) & N_SECT ?
		ft_find_section(header, nlist->n_sect) : (*ptr)->type;
	if (!(nlist->n_type & N_EXT))
		(*ptr)->type = ft_tolower((*ptr)->type);
}

void						ft_init_element(t_symbol_display **list,
	t_symbol_display **ptr)
{
	if (!*list)
	{
		*list = (t_symbol_display*)malloc(sizeof(t_symbol_display));
		*ptr = *list;
		(*ptr)->next = NULL;
		(*ptr)->previous = NULL;
	}
	else
	{
		(*ptr)->next = (t_symbol_display*)malloc(sizeof(t_symbol_display));
		(*ptr)->next->previous = *ptr;
		(*ptr) = (*ptr)->next;
		(*ptr)->next = NULL;
	}
}

void						ft_display_symbols(t_symbol_display *list)
{
	while (list)
	{
		if (list->type != 'U')
			ft_printf("%016lx %c %s\n", list->value, list->type, list->name);
		else
			ft_printf("%16c %c %s\n", ' ', list->type, list->name);
		list = list->next;
	}
}
