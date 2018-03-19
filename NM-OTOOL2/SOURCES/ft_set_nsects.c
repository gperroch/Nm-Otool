/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_nsects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:34:39 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 18:34:53 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

uint32_t		ft_set_nsects(t_load_command *load_cmd, t_generic_file *gen)
{
	uint32_t	nsects;

	nsects = ((t_segment_command_64*)load_cmd)->nsects;
	if (gen->arch == 32)
		nsects = ((t_segment_command*)load_cmd)->nsects;
	if (gen->endian_mach == LITTLEEND)
		nsects = ft_swap_endian_32bit(nsects);
	return (nsects);
}
