/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_sections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:55:42 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 18:33:14 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void			*ft_iter_sections(t_load_command *load_cmd,
	t_generic_file *gen, int section_counter)
{
	uint32_t	cmd;
	uint32_t	nsects;
	void		*section;

	cmd = load_cmd->cmd;
	nsects = ft_set_nsects(load_cmd, gen);
	if (gen->endian_mach == LITTLEEND)
		cmd = ft_swap_endian_32bit(cmd);
	if (cmd == LC_SEGMENT || cmd == LC_SEGMENT_64)
		section_counter -= (nsects - 1);
	section = (char*)load_cmd + ft_arch_gateway(gen->arch, SEGMENT_COMMAND);
	while (section_counter < gen->n_sect)
	{
		section = (char*)section + ft_arch_gateway(gen->arch, SECTION);
		if (!ft_bounds_security(gen, section))
			return (0);
		section_counter++;
	}
	return (section);
}
