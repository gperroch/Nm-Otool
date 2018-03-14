/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_texttext_sections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:01:53 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 12:02:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_iter_texttext_sections(t_load_command *load_command,
	t_mach_header_64 *header, uint32_t *ncmds, int arch)
{
	uint32_t		nsects;
	t_section_64	*section;
	void			*content;
	int				size_segment_command;

	if (arch == 32)
		size_segment_command = sizeof(t_segment_command);
	else
		size_segment_command = sizeof(t_segment_command_64);

	nsects = 0;
	section = (t_section_64*)((char*)load_command
		+ size_segment_command);
	while (nsects < ((struct segment_command*)load_command)->nsects
		&& ft_strcmp(section->sectname, "__text")
		&& ft_strcmp(section->segname, "__TEXT"))
	{
		section = (t_section_64*)((char*)section + sizeof(t_section_64));
		nsects++;
	}
	if (!ft_strcmp(section->sectname, "__text")
		&& !ft_strcmp(section->segname, "__TEXT"))
	{
		content = (char*)header + section->offset;
		ft_dump_mem(content, section->size, 16, header);
		*ncmds = header->ncmds;
	}
}
