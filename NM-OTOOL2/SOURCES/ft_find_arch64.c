/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_arch64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:29:19 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 16:25:50 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int					ft_find_arch64(t_generic_file *gen, uint32_t i)
{
	char				*cputype;
	void				*fat_arch;

	fat_arch = (char*)(gen->fat_header) + sizeof(struct fat_header)
		+ i * ft_arch_gateway(gen->arch, FAT_ARCH);
	if (!ft_bounds_security(gen, fat_arch))
	{
		ft_errors(CORRUPTED, gen->file_name);
		exit(EXIT_FAILURE);
	}
	if (gen->endian_fat == BIGEND)
		cputype = ft_get_arch_type(((struct fat_arch_64*)fat_arch)->cputype);
	else if (gen->endian_fat == LITTLEEND)
		cputype = ft_get_arch_type(
			ft_swap_endian_32bit(((struct fat_arch_64*)fat_arch)->cputype));
	else
		cputype = ft_strdup("undefined");
	if (!ft_strcmp(cputype, "x86_64"))
		return (1);
	return (0);
}
