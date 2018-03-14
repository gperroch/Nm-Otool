/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_texttext_section.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:00:45 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 12:00:57 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_find_texttext_section(t_mach_header_64 *header, int arch) // FUSIONNER CES FONCTIONS AVEC CELLES POUR NM. Attention, celles-ci gerent les 32 et 64 bits, pas celles de NM(?).
{
	t_load_command	*load_command;
	uint32_t		ncmds;
	int				size_mach_header;

	ncmds = 0;
	if (arch == 32)
		size_mach_header = sizeof(t_mach_header);
	else
		size_mach_header = sizeof(t_mach_header_64);
	load_command = (t_load_command*)((char*)header + size_mach_header);
	while (ncmds < header->ncmds)
	{
		ft_iter_texttext_sections(load_command, header, &ncmds, arch);
		load_command = (t_load_command*)((char*)load_command
			+ load_command->cmdsize);
		ncmds++;
	}
}
