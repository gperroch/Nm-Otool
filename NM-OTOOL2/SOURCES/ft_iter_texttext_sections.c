/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_texttext_sections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:01:53 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 16:04:53 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_iter_texttext_sections(t_load_command *load_command,
	uint32_t *ncmds, t_generic_file *gen)
{
	uint32_t		nsects;
	uint32_t		nsectsmax;
	t_section_64	*section;
	int				size_segment_command;

	nsects = -1;
	size_segment_command = gen->arch == 32 ?
		sizeof(t_segment_command) : sizeof(t_segment_command_64);
	section = (t_section_64*)((char*)load_command + size_segment_command);
	nsectsmax = gen->arch == 32 ?
		((struct segment_command*)load_command)->nsects :
		((struct segment_command_64*)load_command)->nsects;
	if (gen->endian_mach == LITTLEEND)
		nsectsmax = ft_swap_endian_32bit(nsectsmax);
	while (++nsects < nsectsmax && ft_strcmp(section->sectname, "__text")
		&& ft_strcmp(section->segname, "__TEXT"))
		section = gen->arch == 32 ?
			(t_section_64*)((char*)section + sizeof(t_section))
			: (t_section_64*)((char*)section + sizeof(t_section_64));
	if (!ft_strcmp(section->sectname, "__text")
		&& !ft_strcmp(section->segname, "__TEXT"))
		ft_display_section_content(section, ncmds, gen);
}
