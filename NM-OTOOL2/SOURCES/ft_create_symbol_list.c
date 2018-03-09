/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_symbol_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:23:58 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 14:55:12 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_create_symbol_list(void *symtab, void *strtab, t_symtab_command *symtab_command, t_generic_file *gen)
{
	t_symbol_display		*list;
	t_symbol_display		*ptr;
	uint32_t				symbol_counter;
	uint32_t				symbol_max;

	gen->nlist = symtab;
	gen->nlist_64 = symtab;

	symbol_counter = 0;
	symbol_max = 0;
	if (gen->endian_mach == BIGEND)
		symbol_max = symtab_command->nsyms;
	else if (gen->endian_mach == LITTLEEND)
		symbol_max = ft_swap_endian_32bit(symtab_command->nsyms);
	list = NULL;
	while (symbol_counter < symbol_max)
	{
/*		if ((gen->arch == 32 && !ft_bounds_security(gen, gen->nlist)) || (gen->arch == 64 && !ft_bounds_security(gen, gen->nlist_64))) // Necessite gen.file_size et gen.file_start pour fonctionner
			return (NULL);*/
		/******************************************************/
		if (gen->endian_mach == BIGEND)
		{
			gen->n_type = gen->arch == 32 ? gen->nlist->n_type : gen->nlist_64->n_type;
			gen->n_sect = gen->arch == 32 ? gen->nlist->n_sect : gen->nlist_64->n_sect;
			gen->n_desc = gen->arch == 32 ? gen->nlist->n_desc : gen->nlist_64->n_desc;
			gen->n_value = gen->arch == 32 ? gen->nlist->n_value : gen->nlist_64->n_value;
			gen->n_strx = gen->arch == 32 ? gen->nlist->n_un.n_strx : gen->nlist_64->n_un.n_strx;
		}
		else if (gen->endian_mach == LITTLEEND)
		{
			gen->n_type = gen->arch == 32 ? gen->nlist->n_type : gen->nlist_64->n_type;
			gen->n_sect = gen->arch == 32 ? gen->nlist->n_sect : gen->nlist_64->n_sect;
			gen->n_desc = gen->arch == 32 ? gen->nlist->n_desc : gen->nlist_64->n_desc;
			gen->n_value = gen->arch == 32 ? ft_swap_endian_32bit(gen->nlist->n_value) : ft_swap_endian_32bit(gen->nlist_64->n_value);
			gen->n_strx = gen->arch == 32 ? ft_swap_endian_32bit(gen->nlist->n_un.n_strx) : ft_swap_endian_32bit(gen->nlist_64->n_un.n_strx);
		}
		/******************************************************/
		if (!(gen->n_type & N_STAB))
		{
			ft_init_element(&list, &ptr);
			//ft_set_element(&ptr, nlist, header, strtab); // 64bit
			ft_set_element(&ptr, gen, strtab); // 64bit
		}
		gen->nlist = (struct nlist*)((char*)gen->nlist + sizeof(struct nlist)); // GATEWAY
		gen->nlist_64 = (struct nlist_64*)((char*)gen->nlist_64 + sizeof(struct nlist_64)); // GATEWAY
		symbol_counter++;
	}
	return (list);
}






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
	tmp_type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section(gen) : (*ptr)->type;
/*	if (gen->endian_mach == LITTLEEND)
	{
		tmp_type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section(gen) : (*ptr)->type; // CHANGER FIND_SECTION // 64bit
	}
	else if (gen->endian_mach == BIGEND)
	{
		tmp_type = (gen->n_type & N_TYPE) & N_SECT ? ft_find_section_bigendian(gen) : (*ptr)->type; // CHANGER FIND_SECTION // 64bit
	}*/
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
