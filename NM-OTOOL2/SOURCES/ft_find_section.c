/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:36:04 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 18:34:07 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char				ft_find_section(t_generic_file *gen)
{
	t_load_command	*load_cmd;
	void			*section;
	int				section_counter;

	load_cmd = (t_load_command*)((char*)(gen->header)
		+ ft_arch_gateway(gen->arch, MACH_HEADER));
	section_counter = ft_iter_load_commands(gen, &load_cmd);
	if (!ft_bounds_security(gen, load_cmd))
	{
		ft_errors(CORRUPTED, gen->file_name);
		exit(1);
	}
	section = ft_iter_sections(load_cmd, gen, section_counter);
	return (ft_section_type(section));
}
