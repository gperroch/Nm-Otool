/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:50:36 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/21 19:31:35 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display		*ft_create_element(t_generic_file *gen, void *strtab)
{
	t_symbol_display		*ptr;
	char					tmp_type;

	ptr = (t_symbol_display*)malloc(sizeof(t_symbol_display));
	ptr->next = NULL;
	ptr->previous = NULL;
	ptr->value = gen->n_value;
	ptr->name = &((char*)strtab)[gen->n_strx];
	ptr->type = 'U';
	ptr->type = (gen->n_type & N_STAB) == N_STAB ? '-' : ptr->type;
	ptr->type = ((gen->n_type & N_TYPE)) == N_UNDF ? 'U' : ptr->type;
	ptr->type = ((gen->n_type & N_TYPE)) == N_INDR ? 'I' : ptr->type;
	ptr->type = ((gen->n_type & N_TYPE)) == N_ABS ? 'A' : ptr->type;
	ptr->type = ((gen->n_type & N_TYPE)) == N_PBUD ? 'U' : ptr->type;
	tmp_type = ptr->type;
	tmp_type = ((gen->n_type & N_TYPE)) == N_SECT ?
		ft_find_section(gen) : ptr->type;
	if (tmp_type && ptr->type == 'U')
		ptr->type = tmp_type;
	if (!(gen->n_type & N_EXT))
		ptr->type = ft_tolower(ptr->type);
	return (ptr);
}
