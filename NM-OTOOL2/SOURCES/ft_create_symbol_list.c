/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_symbol_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:23:58 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 16:46:18 by gperroch         ###   ########.fr       */
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
		gen->n_type = gen->arch == 32 ? gen->nlist->n_type : gen->nlist_64->n_type;
		gen->n_sect = gen->arch == 32 ? gen->nlist->n_sect : gen->nlist_64->n_sect;
		gen->n_desc = gen->arch == 32 ? gen->nlist->n_desc : gen->nlist_64->n_desc;
		gen->n_value = gen->arch == 32 ? gen->nlist->n_value : gen->nlist_64->n_value;
		gen->n_strx = gen->arch == 32 ? gen->nlist->n_un.n_strx : gen->nlist_64->n_un.n_strx;
		if (gen->endian_mach == LITTLEEND)
		{
			gen->n_value = ft_swap_endian_32bit(gen->n_value);
			gen->n_strx = ft_swap_endian_32bit(gen->n_strx);
		}
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






void						ft_set_element(t_symbol_display **ptr, t_generic_file *gen, void *strtab) // GATEWAY
{
	char					tmp_type;

	(*ptr)->value = gen->n_value;
	(*ptr)->name = &((char*)strtab)[gen->n_strx];
	(*ptr)->type = 'U';
	(*ptr)->type = gen->n_type & N_STAB ? '-' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_UNDF ? 'U' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_INDR ? 'I' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_ABS ? 'A' : (*ptr)->type;
	(*ptr)->type = (gen->n_type & N_TYPE) & N_PBUD ? 'U' : (*ptr)->type;
	tmp_type = (*ptr)->type;
	tmp_type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section(gen) : (*ptr)->type;
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

char						ft_section_type(t_section_64 *section)
{
	char					res;

	if (!ft_has_print(section->sectname))
		return (0);
	res = 'S';
	res = !ft_strcmp(section->sectname, "__text") ? 'T' : res;
	res = !ft_strcmp(section->sectname, "__data") ? 'D' : res;
	res = !ft_strcmp(section->sectname, "__bss") ? 'B' : res;
	res = !ft_strcmp(section->sectname, "__common") &&
			ft_strcmp(section->segname, "__DATA") ? 'C' : res;
	return (res);
}

int						ft_has_print(char *str)
{
	char				has_print;
	int					len;

	has_print = 0;
	len = ft_strlen(str);
	while (len > 0)
	{
		if (ft_isprint(str[len - 1]))
			has_print = 1;
		len--;
	}
	return (has_print);
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

void					ft_sort_list_symbols(t_symbol_display **list)
{
	t_symbol_display	*ptr;
	t_symbol_display	*ptr2;
	char				modified;

	modified = 1;
	while (modified)
	{
		modified = 0;
		ptr = *list;
		while (ptr && ptr->next)
		{
			ptr2 = ptr->next;
			if (ft_strcmp(ptr->name, ptr2->name) > 0)
			{
				ft_set_previous_and_next(ptr, ptr2, list);
				modified = 1;
			}
			ptr = ptr2;
		}
	}
}

void					ft_set_previous_and_next(t_symbol_display *ptr,
	t_symbol_display *ptr2, t_symbol_display **list)
{
	if (ptr->previous)
		(ptr->previous)->next = ptr2;
	else
		*list = ptr2;
	if (ptr2->next)
		(ptr2->next)->previous = ptr;
	ptr->next = ptr2->next;
	ptr2->previous = ptr->previous;
	ptr->previous = ptr2;
	ptr2->next = ptr;
}
