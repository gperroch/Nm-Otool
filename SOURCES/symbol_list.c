/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:39:00 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/31 17:41:47 by gperroch         ###   ########.fr       */
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

t_symbol_display			*ft_create_symbol_list_bigendian(void *symtab, void *strtab, t_symtab_command *symtab_command, t_generic_file *gen)
{
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	int				symbol_counter;

	gen->nlist = symtab;
	gen->nlist_64 = symtab;

	symbol_counter = 0;
	list = NULL;
//	dump_mem(symtab, ft_swap_endian_32bit(symtab_command->nsyms) * sizeof(struct nlist_64), 12, "nlist");
	while (symbol_counter < ft_swap_endian_32bit(symtab_command->nsyms))
	{
		if (!ft_bounds_security(gen, gen->nlist) || !ft_bounds_security(gen, gen->nlist_64))
			return (NULL);
		gen->n_type = gen->arch == 32 ? gen->nlist->n_type : gen->nlist_64->n_type;
		gen->n_sect = gen->arch == 32 ? gen->nlist->n_sect : gen->nlist_64->n_sect;
		gen->n_desc = gen->arch == 32 ? gen->nlist->n_desc : gen->nlist_64->n_desc;
		gen->n_value = gen->arch == 32 ? ft_swap_endian_32bit(gen->nlist->n_value) : ft_swap_endian_32bit(gen->nlist_64->n_value);
		gen->n_strx = gen->arch == 32 ? ft_swap_endian_32bit(gen->nlist->n_un.n_strx) : ft_swap_endian_32bit(gen->nlist_64->n_un.n_strx);
		if (!(gen->n_type & N_STAB))
		{
			ft_init_element(&list, &ptr);
			ft_set_element(&ptr, gen, strtab);
		}
		gen->nlist = (struct nlist*)((char*)gen->nlist + sizeof(struct nlist));
		gen->nlist_64 = (struct nlist_64*)((char*)gen->nlist_64 + sizeof(struct nlist_64));
		symbol_counter++;
	}
	return (list);
}


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
//	dump_mem(symtab, symtab_command->nsyms * sizeof(struct nlist_64), 12, "nlist2");
	while (symbol_counter < symtab_command->nsyms)
	{
		if ((gen->arch == 32 && !ft_bounds_security(gen, gen->nlist)) || (gen->arch == 64 && !ft_bounds_security(gen, gen->nlist_64)))
			return (NULL);
		gen->n_type = gen->arch == 32 ? gen->nlist->n_type : gen->nlist_64->n_type;
		gen->n_sect = gen->arch == 32 ? gen->nlist->n_sect : gen->nlist_64->n_sect;
		ft_printf("gen->nlist->n_sect:%d gen->nlist_64->n_sect:%d gen->arch:%d\n", gen->nlist->n_sect, gen->nlist_64->n_desc, gen->arch);
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
	char					tmp_type;

	(*ptr)->value = gen->n_value;
	//(*ptr)->name = &((char*)strtab)[(nlist->n_un).n_strx]; // !!
	(*ptr)->name = &((char*)strtab)[gen->n_strx];
	(*ptr)->type = 'U';
	(*ptr)->type = gen->n_type & N_STAB ? '-' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_UNDF ? 'U' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_INDR ? 'I' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_ABS ? 'A' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_PBUD ? 'U' : (*ptr)->type;
	//(*ptr)->type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section(header, gen->n_sect) : (*ptr)->type; // CHANGER FIND_SECTION // 64bit
	tmp_type = (*ptr)->type;
	if (gen->endian_mach == LITTLEEND)
	{
		tmp_type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section(gen) : (*ptr)->type; // CHANGER FIND_SECTION // 64bit
	}
	else if (gen->endian_mach == BIGEND)
	{
		tmp_type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section_bigendian(gen) : (*ptr)->type; // CHANGER FIND_SECTION // 64bit
	}
	if (tmp_type && (*ptr)->type == 'U')
		(*ptr)->type = tmp_type;
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

void						ft_display_symbols(t_symbol_display *list, t_generic_file *gen) // A OPTIMISER AU NIVEAU DES STRINGS D'AFFICHAGE // PROBLEME SUR L'ADDRESS
{
	while (list)
	{
		if (gen->arch == 64)
		{
			if (list->type == 'U' || list->type == 'u')
				ft_printf("%16c %c %s\n", ' ', list->type, list->name);
			else
				ft_printf("%016lx %c %s\n", list->value + 0x100000000, list->type, list->name); // Bizzare de devoir faire ca
		}
		else if (gen->arch == 32)
		{
			if (list->type == 'U' || list->type == 'u')
				ft_printf("%8c %c %s\n", ' ', list->type, list->name);
			else
				ft_printf("%08x %c %s\n", list->value, list->type, list->name);
		}
		list = list->next;
	}
}
