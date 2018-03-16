/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_texttext_sections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:01:53 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 17:42:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_iter_texttext_sections(t_load_command *load_command, uint32_t *ncmds, t_generic_file *gen)
{
	uint32_t		nsects;
	uint32_t		nsectsMax;
	t_section_64	*section;
	void			*content;
	int				size_segment_command;


	if (gen->arch == 32)
		size_segment_command = sizeof(t_segment_command);
	else
		size_segment_command = sizeof(t_segment_command_64);

	nsects = 0;
	section = (t_section_64*)((char*)load_command
		+ size_segment_command);
//	ft_printf("1\n");
	if (gen->arch == 32)
		nsectsMax = ((struct segment_command*)load_command)->nsects;
	else
		nsectsMax = ((struct segment_command_64*)load_command)->nsects;
	if (gen->endian_mach == LITTLEEND)
		nsectsMax = ft_swap_endian_32bit(nsectsMax);

	if (gen->arch == 32)
	{
//		ft_printf("\tA2 %d\n", nsectsMax);
		while (nsects < nsectsMax
			&& ft_strcmp(((t_section*)section)->sectname, "__text")
			&& ft_strcmp(((t_section*)section)->segname, "__TEXT"))
		{
//			ft_printf("\tA3\n");
			if (gen->arch == 32)
				section = (t_section_64*)((char*)section + sizeof(t_section));
			else
				section = (t_section_64*)((char*)section + sizeof(t_section_64));
			nsects++;
		}
	}
	else
	{
//		ft_printf("\tB2\n");
		while (nsects < nsectsMax
			&& ft_strcmp(section->sectname, "__text")
			&& ft_strcmp(section->segname, "__TEXT"))
		{
//			ft_printf("\tB3\n");
			if (gen->arch == 32)
				section = (t_section_64*)((char*)section + sizeof(t_section));
			else
				section = (t_section_64*)((char*)section + sizeof(t_section_64));
			nsects++;
		}
	}
//	ft_printf("2\n");
	if (!ft_strcmp(section->sectname, "__text")
		&& !ft_strcmp(section->segname, "__TEXT"))
	{
//		ft_printf("\tC2\n");
		uint32_t		sectionOffset;
		uint32_t		sectionSize;
		if (gen->arch == 32)
		{
			sectionOffset = ((t_section*)section)->offset;
			sectionSize = ((t_section*)section)->size;
		}
		else
		{
			sectionOffset = ((t_section_64*)section)->offset;
			sectionSize = ((t_section_64*)section)->size;
		}
		if (gen->endian_mach == LITTLEEND)
		{
			sectionOffset = ft_swap_endian_32bit(sectionOffset);
			sectionSize = ft_swap_endian_32bit(sectionSize);
		}

		if (gen->arch == 32)
		{
//			ft_printf("D1\n");
			content = (char*)(gen->header) + sectionOffset;
//			ft_printf("D2 content[%p] = (char*)(gen->header)[%p] + sectionOffset[%d];\n", content, (char*)(gen->header), sectionOffset);
			ft_dump_mem_32(content, sectionSize, 16, gen->header);
		}
		else
		{
//			ft_printf("E1\n");
			content = (char*)(gen->header) + sectionOffset;
			ft_dump_mem(content, sectionSize, 16, gen->header);
		}
		*ncmds = gen->header->ncmds;
	}
}
