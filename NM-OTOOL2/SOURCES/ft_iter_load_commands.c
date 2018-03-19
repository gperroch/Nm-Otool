/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_load_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:26:22 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 18:34:51 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int				ft_iter_load_commands(t_generic_file *gen,
	t_load_command **load_cmd)
{
	int			section_counter;
	uint32_t	nsects;

	section_counter = 0;
	while (section_counter < gen->n_sect)
	{
		if (!ft_bounds_security(gen, *load_cmd))
			ft_errors(CORRUPTED, gen->file_name); // Changer tous les appels a ft_errors(CORRUPTED)
		nsects = ft_set_nsects(*load_cmd, gen);
		if ((gen->endian_mach == LITTLEEND &&
			(ft_swap_endian_32bit((*load_cmd)->cmd) == LC_SEGMENT
			|| ft_swap_endian_32bit((*load_cmd)->cmd) == LC_SEGMENT_64))
			|| (gen->endian_mach == BIGEND && ((*load_cmd)->cmd == LC_SEGMENT
			|| (*load_cmd)->cmd == LC_SEGMENT_64)))
			section_counter += nsects;
		if (section_counter < gen->n_sect && gen->endian_mach == LITTLEEND)
			*load_cmd = (t_load_command*)((char*)(*load_cmd)
			+ ft_swap_endian_32bit((*load_cmd)->cmdsize));
		else if (section_counter < gen->n_sect && gen->endian_mach == BIGEND)
			*load_cmd = (t_load_command*)((char*)(*load_cmd)
			+ (*load_cmd)->cmdsize);
	}
	return (section_counter);
}
