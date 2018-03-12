/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bounds_security.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:48:40 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:53:58 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							ft_bounds_security(t_generic_file *gen, void *ptr)
{
	void					*max_addr;

	max_addr = (char*)(gen->file_start) + gen->file_size;
	if ((char*)ptr - (char*)max_addr > 0)
	{
		ft_errors(CORRUPTED, 0, gen->file_name);
		//ft_printf("ft_nm: %s truncated or malformed object max_addr[%p] ptr[%p]\n\n", gen->file_name, max_addr, ptr);
		return (0);
	}
	return (1);
}
