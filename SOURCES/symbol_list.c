/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:39:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/25 12:31:24 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/* VERSION 64bit
t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab,
	t_symtab_command *symtab_command, t_mach_header_64 *header)
{
//	struct nlist_64			*nlist; // 64bit
	struct nlist			*nlist; // 32bit
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
		//nlist = (struct nlist_64*)((char*)nlist + sizeof(struct nlist_64)); // 64bit
		nlist = (struct nlist*)((char*)nlist + sizeof(struct nlist)); // 32bit
		symbol_counter++;
	}
	return (list);
}

//void						ft_set_element(t_symbol_display **ptr, struct nlist_64 *nlist, t_mach_header_64 *header, void *strtab) // 64bit
void						ft_set_element(t_symbol_display **ptr, struct nlist *nlist, t_mach_header_64 *header, void *strtab) // 32bit
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
*/









/* VERSION GATEWAY */

t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab, t_symtab_command *symtab_command, t_generic_file *gen)
{
//	struct nlist_64			*nlist; // 64bit
//	struct nlist			*nlist; // 32bit
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	uint32_t				symbol_counter;

	//nlist = symtab; // 64bit
	gen->nlist = symtab; // GATEWAY
	gen->nlist_64 = symtab; // GATEWAY



	symbol_counter = 0;
	list = NULL;
	while (symbol_counter < symtab_command->nsyms)
	{
		gen->n_type = gen->arch == 32 ? gen->nlist->n_type : gen->nlist_64->n_type;
		gen->n_sect = gen->arch == 32 ? gen->nlist->n_sect : gen->nlist_64->n_sect;
		gen->n_desc = gen->arch == 32 ? gen->nlist->n_desc : gen->nlist_64->n_desc;
		gen->n_value = gen->arch == 32 ? gen->nlist->n_value : gen->nlist_64->n_value;
		gen->n_strx = gen->arch == 32 ? gen->nlist->n_un.n_strx : gen->nlist_64->n_un.n_strx;
		if (!(gen->n_type & N_STAB))
		{
			ft_init_element(&list, &ptr);
			//ft_set_element(&ptr, nlist, header, strtab); // 64bit
			ft_set_element(&ptr, gen, strtab); // 64bit
		}
		//nlist = (struct nlist_64*)((char*)nlist + sizeof(struct nlist_64)); // 64bit
		gen->nlist = (struct nlist*)((char*)gen->nlist + sizeof(struct nlist)); // GATEWAY
		gen->nlist_64 = (struct nlist_64*)((char*)gen->nlist_64 + sizeof(struct nlist_64)); // GATEWAY
		symbol_counter++;
	}
	return (list);
}

//void						ft_set_element(t_symbol_display **ptr, struct nlist_64 *nlist, t_mach_header_64 *header, void *strtab) // 64bit
//void						ft_set_element(t_symbol_display **ptr, struct nlist *nlist, t_mach_header_64 *header, void *strtab) // 32bit
void						ft_set_element(t_symbol_display **ptr, t_generic_file *gen, void *strtab) // GATEWAY
{
	(*ptr)->value = gen->n_value;
	//(*ptr)->name = &((char*)strtab)[(nlist->n_un).n_strx]; // !!
	(*ptr)->name = &((char*)strtab)[gen->n_strx];
	(*ptr)->type = 'U';
	(*ptr)->type = gen->n_type & N_STAB ? '-' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_UNDF ? 'U' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_ABS ? 'A' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_INDR ? 'I' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_PBUD ? 'U' : (*ptr)->type;
	//(*ptr)->type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section(header, gen->n_sect) : (*ptr)->type; // CHANGER FIND_SECTION // 64bit
	(*ptr)->type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section(gen) : (*ptr)->type; // CHANGER FIND_SECTION // 64bit
	if (!(gen->n_type & N_EXT))
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
