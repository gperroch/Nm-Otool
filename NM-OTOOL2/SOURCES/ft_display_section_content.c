/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_section_content.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:04:28 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 16:04:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void			ft_display_section_content(t_section_64 *section,
	uint32_t *ncmds, t_generic_file *gen)
{
	uint32_t	sectionoffset;
	uint32_t	sectionsize;
	void		*content;

	sectionoffset = gen->arch == 32 ?
		((t_section*)section)->offset : ((t_section_64*)section)->offset;
	sectionsize = gen->arch == 32 ?
		((t_section*)section)->size : ((t_section_64*)section)->size;
	if (gen->endian_mach == LITTLEEND)
	{
		sectionoffset = ft_swap_endian_32bit(sectionoffset);
		sectionsize = ft_swap_endian_32bit(sectionsize);
	}
	content = (char*)(gen->header) + sectionoffset;
	if (gen->arch == 32)
		ft_dump_mem_32(content, sectionsize, 16, gen->header);
	else
		ft_dump_mem(content, sectionsize, 16, gen->header);
	*ncmds = gen->header->ncmds;
}
